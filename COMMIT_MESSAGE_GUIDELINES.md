# Commit Message Guidelines for Aura (Unreal Engine 5)

Follow these rules to make your commit history readable and useful for all contributors and automation tools (like GitHub).

## Commit Message Structure

Each commit message should be structured as follows:

```
<type>(<scope>): <short summary>

[Optional body]

[Optional footer]
```

### Types
- **feat**: New feature (e.g., new gameplay mechanic, new asset type)
- **fix**: Bug fix (e.g., crash fix, logic correction)
- **docs**: Documentation changes (e.g., README, comments)
- **style**: Formatting, missing semicolons, etc. (no code logic change)
- **refactor**: Code change that neither fixes a bug nor adds a feature
- **perf**: Performance improvement
- **test**: Adding or updating tests
- **build**: Changes to build scripts or external dependencies
- **ci**: Changes to CI/CD configuration
- **chore**: Maintenance (e.g., updating dependencies, Unreal project settings)

### Scope
Scope is optional but recommended. Use it to specify the area affected, such as:
- `gameplay`, `ui`, `assets`, `build`, `docs`, `blueprints`, `materials`, `audio`, `ai`, `input`, `config`, etc.

### Examples
- `feat(gameplay): add new magic system`
- `fix(ui): correct health bar alignment`
- `docs: update README with setup instructions`
- `refactor(blueprints): simplify enemy spawn logic`
- `chore(config): update DefaultEngine.ini for new map`

### Body (Optional)
Use the body to explain what and why vs. how. Include context for complex changes.

### Footer (Optional)
Reference issues or PRs, e.g., `Closes #42`.

---

## Tips for Unreal Engine 5 Projects
- Mention affected assets or blueprints if relevant (e.g., `BP_HealthPotion`)
- For binary asset changes, describe the change (e.g., `feat(assets): add new dungeon textures`)
- For config changes, specify the file (e.g., `chore(config): update DefaultInput.ini for new action`)

## Why Follow This?
- Clear history for all contributors
- Easier code reviews and changelogs
- Better integration with GitHub tools

## Example from Aura Commit History

```
Ghost Globe

feat: Add ghost globe trailing effect and pickup animations

- Implement ghost progress bars that smoothly trail behind main health/mana globes
- Add interpolation system with configurable delay and speed for smooth transitions
- Create ghost-specific material brush system for visual customization
- Add proper initialization logic to sync ghost and main globes on startup
- Implement Timeline-based bob and spin animations for pickup objects
- Enhance fire area damage for better ghost globe demonstration
- Add Event Tick inheritance support in child progress bar widgets
- Create reusable ghost globe system in base WBP_GlobeProgressBar widget
```

This example follows the guidelines: it uses a type, scope, clear summary, a detailed body explaining the problem, reproduction steps, and the resolution, plus a footer referencing a related issue.

---

For more details, see [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/).
