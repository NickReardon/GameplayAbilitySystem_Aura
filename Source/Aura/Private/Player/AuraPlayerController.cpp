// Copyright Nicholas Reardon


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}



void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	if (bAutoRunning) AutoRun();

	GEngine->AddOnScreenDebugMessage(20, 1.0f, FColor::Red, FString::Printf(TEXT("FollowTime: %f"), FollowTime));
}

void AAuraPlayerController::AutoRun()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;

	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagPressed,
		&ThisClass::AbilityInputTagReleased,
		&ThisClass::AbilityInputTagHeld);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
	
	
	

}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();



	
	/*
	 * A. LastActor is not valid and ThisActor is null
	 * - do nothing
	 *
	 * B. LastActor is not valid and ThisActor is valid
	 * - highlight ThisActor
	 *
	 * C. LastActor is valid and ThisActor is null
	 *  - unhighlight LastActor
	 *
	 *  D. Both valid and different
	 *	- unhighlight LastActor
	 *	- highlight ThisActor
	 *
	 * E. Both valid and the same
	 * - do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// Case A
			return;
		}
		else
		{
			ThisActor->HighlightActor();
			// Case B
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnhighlightActor();
			// Case C
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnhighlightActor();
				ThisActor->HighlightActor();
				// Case D
			}
			else
			{
				// Case E
				return;
			}
		}
	}

}

void AAuraPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(AuraGameplayTags::TAG_INPUTTAG_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}

}

void AAuraPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::TAG_INPUTTAG_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		if (FollowTime <= ShortPressThreshold)
		{
			APawn* ControlledPawn = GetPawn();
			if (ControlledPawn)
			{
				FHitResult NavChannelCursorHitResult;
				GetHitResultUnderCursor(ECC_GameTraceChannel1, false, NavChannelCursorHitResult);
				if (NavChannelCursorHitResult.bBlockingHit)
				{
					// Projecting a point from the cursor impact point to the NavMesh with a larger-than-default
					// Query Extent, so there are better chances to reach for the NavMesh and return a point,
					// then generating a path from the pawn location to this point (only if found).
     
					FNavLocation ImpactPointNavLocation;
					// NOTE: Default Query Extend = FVector(50.0f, 50.0f, 250.0f)
					const FVector QueryingExtent = FVector(400.0f, 400.0f, 250.0f);
					const FNavAgentProperties& NavAgentProps = GetNavAgentPropertiesRef();
					UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
					const bool bNavLocationFound = NavSystem->ProjectPointToNavigation(NavChannelCursorHitResult.ImpactPoint, ImpactPointNavLocation, QueryingExtent, &NavAgentProps);
					
					if (bNavLocationFound && ((ImpactPointNavLocation.Location - ControlledPawn->GetActorLocation()).Length() > AutoRunAcceptanceRadius))
					{
						UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), ImpactPointNavLocation);
						if (NavigationPath && NavigationPath->PathPoints.Num() > 0)
						{
							Spline->ClearSplinePoints();
							for (const FVector& PathPoint : NavigationPath->PathPoints)
							{
								Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World);
								DrawDebugSphere(GetWorld(), PathPoint, 5.0f, 12, FColor::Green, false, 3.0f);
							}
							
							CachedDestination = NavigationPath->PathPoints.Last();
							DrawDebugSphere(GetWorld(), CachedDestination, AutoRunAcceptanceRadius, 12, FColor::Red, false, 3.0f);
							bAutoRunning = true;
						}
						
					}
				}       
			}

		}
		FollowTime = 0.0f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::TAG_INPUTTAG_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_PhysicsBody, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn<APawn>())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			if ((CachedDestination - ControlledPawn->GetActorLocation()).Length() > AutoRunAcceptanceRadius)
			{
				// Only add movement input if the destination is far enough away
				// This prevents the player from moving when they are already close to the destination
				ControlledPawn->AddMovementInput(WorldDirection);
			}
		}

		
	}
	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));

	}
	return AuraAbilitySystemComponent;
}
