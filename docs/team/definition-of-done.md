# Definition of Done (Team)

This document defines what “done” means for work merged into the `main` branch. A pull request is only ready to merge when **all** of the following conditions are met.

## Required (Minimum)

- Work is completed on a short-lived branch (no direct commits to `main`)
- A pull request is opened early (not at the end of development)
- At least one teammate review is completed and approved
- All CI checks pass (lint/format checks and automated tests)
- Code follows team standards (style, structure, naming, readability)
- Any new behavior includes at least starter-level automated tests (unit or smoke tests) **OR** a written test plan explaining what was tested and how
- Documentation is updated when behavior or usage changes (README or relevant docs)

## Repository Enforcement

The repository enforces the following rules on the `main` branch:

- Pull requests are required before merging
- At least one approving review is required
- CI status checks must pass before merging

## Notes

- Small, focused pull requests are preferred for faster and clearer reviews.
- If automated tests are not feasible, the pull request must include a brief **Test Plan** section describing manual verification steps.