# Contributing

## Branch naming
Use short-lived branches:
- `week5/ci-setup`
- `feature/<short-name>`
- `fix/<short-name>`

## PR expectations
- Open PRs early (drafts are OK)
- Keep PRs small and focused
- Link the related issue or assignment section when applicable
- CI must be green before merge

## Review expectations
Reviewers should check:
- Code is readable and follows repository standards
- Tests exist or are updated when behavior changes
- No secrets or sensitive data are committed
- CI checks pass

## Run checks locally

### Windows (PowerShell / Developer PowerShell)
From repo root:

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure