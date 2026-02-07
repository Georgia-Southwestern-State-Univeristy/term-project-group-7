# Contributing

## Branch naming
Use short-lived branches:
- `week5/ci-standards-slice`
- `feature/<short-name>`
- `fix/<short-name>`

## PR expectations
- Open PRs early (draft is OK)
- Keep PRs small and focused
- Link the issue/ticket in the PR description when applicable
- CI must be green before merge

## Review expectations
Reviewers should check:
- Code is readable and follows repo standards
- Tests exist/updated when behavior changes
- No secrets/PII committed
- CI passes

## Run checks locally
From repo root:

```bash
py -m pip install -r requirements.txt
py -m ruff check .
py -m pytest -q
py app.py