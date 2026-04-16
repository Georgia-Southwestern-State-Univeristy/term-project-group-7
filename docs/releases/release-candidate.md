# Release Candidate Summary

## Release Candidate Tag
**Tag:** `rc-v0.9`  
**Date:** 04/16/2026

## Summary
This release candidate represents the team’s near-final semester prototype for a middle-school math learning system.

The current release candidate includes:
- a Windows desktop GUI built in C++
- SQLite-backed question content and analytics data
- a local HTTP API for documented system interfaces
- automated regression and validation tests
- reviewer-facing documentation for release, runbook, user flow, maintenance, triage, and repo alignment

This release candidate is intended to feel like a near-final product milestone rather than a vague checkpoint.

## Core Workflows Expected to Be Stable
The following workflows are expected to work consistently in this release candidate:

1. configure and build the project on Windows with CMake
2. launch the desktop application successfully
3. select a grade level from the main menu
4. choose an operation and complete question flow
5. submit answers and receive immediate feedback
6. use hints during a practice session
7. open the analytics view
8. access the local HTTP health endpoint successfully
9. run automated regression and validation tests successfully

## Major Differences from Beta
Compared to the beta stage, this release candidate improves:
- documentation alignment with the actual project state
- clarity of build, run, and verification instructions
- user-facing and maintainer-facing documentation
- repository navigation for reviewers
- release readiness communication
- final triage visibility for remaining issues
- cleaner handoff for final evaluation

## Remaining Known Risks Before Final Release
- Windows-first execution path limits portability
- runtime success depends on copied local assets such as `questions.db`
- maintainer-facing diagnostics are still lightweight
- packaging/distribution is still course-oriented rather than end-user-oriented
- some historical docs required cleanup to stay aligned with the current release candidate state

## What Must Still Be Completed in Weeks 15–16
- close remaining critical and important triage items
- finalize consistency across all major project documents
- complete final release polish and presentation readiness
- verify the run path again with another reviewer
- replace all placeholder evidence links with final PR, release, and CI references
- prepare the final release after release candidate review

## Release Artifact
- Git tag: `rc-v0.9`
- GitHub release page: RELEASE LINK
- Related PR: PR LINK
- CI run for release candidate: ACTIONS RUN LINK

## Evidence
- Runbook verification results are documented in `docs/final/week14-runbook.md`
- Remaining release risks are documented in `docs/final/week14-triage.md`
- Repository cleanup and alignment work are documented in `docs/final/week14-repo-polish.md`