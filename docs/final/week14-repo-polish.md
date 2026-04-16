# Week 14 Documentation Alignment + Repo Polish

## Purpose
This document records the repository alignment and cleanup work completed for the Week 14 release candidate package.

## What Was Reorganized, Renamed, or Clarified
- clarified the reviewer start path in `README.md`
- added a formal release candidate summary
- added a verified runbook for build, launch, and validation
- added a dedicated user guide
- added a dedicated admin / maintenance guide
- added an interface overview to complement the formal API contract
- added a final triage document for release readiness

## What Confusing or Stale Material Was Removed or Updated
- removed release-candidate wording that incorrectly described the project as CLI-only
- clarified that the primary release candidate experience is Windows-first
- clarified that runtime success depends on copied assets such as `questions.db` and `static/`
- marked older beta deployment guidance as historical rather than current
- improved repo navigation so reviewers can find the correct evaluation docs without guessing

## Where a Reviewer Should Start
A reviewer opening the repository should follow this order:

1. `README.md`
2. `docs/releases/release-candidate.md`
3. `docs/final/week14-runbook.md`
4. `docs/user-guide.md`
5. `docs/admin-guide.md`
6. `docs/api/interface-overview.md`
7. `docs/api/openapi.yaml`
8. `tests/`

## Why This Alignment Work Was Necessary
Week 13 feedback showed that the project needed stronger operational evidence, clearer process visibility, and better alignment between the repository and the real state of the system.

This cleanup work was completed to reduce reviewer confusion and improve release readiness.

## Evidence
- PR: PR LINK
- CI run: ACTIONS RUN LINK
- Release candidate tag: TAG LINK
- Related issues: ISSUE LINK