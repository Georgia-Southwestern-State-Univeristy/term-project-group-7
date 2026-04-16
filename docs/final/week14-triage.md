# Week 14 Final Bug Triage + Fix Progress

## Purpose
This document prioritizes the issues that still threaten final release readiness.

## Priority Definitions
- **Critical:** must fix before final presentation
- **Important:** strongly recommended before final release
- **Optional:** good polish if time allows

## 1. Documentation drift across older files
- **Priority:** Critical
- **Description:** Some historical docs still describe earlier project states and can confuse reviewers if left uncorrected.
- **Affected Component:** Documentation
- **Assigned Owner:** Ridhwaan
- **Expected Disposition:** fix in Week 15
- **Status This Week:** in progress
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 2. README alignment with actual release candidate
- **Priority:** Critical
- **Description:** The root README must consistently describe the Windows GUI, local HTTP API, SQLite runtime assets, and reviewer start path.
- **Affected Component:** Repository onboarding
- **Assigned Owner:** David
- **Expected Disposition:** fix in Week 15
- **Status This Week:** improved
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 3. Runtime dependency on `questions.db`
- **Priority:** Critical
- **Description:** If `questions.db` is not copied into the runtime output directory, the GUI question flow and analytics behavior can fail.
- **Affected Component:** Runtime assets / local data
- **Assigned Owner:** Grey
- **Expected Disposition:** verify and document in Week 15
- **Status This Week:** in progress
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 4. Runtime dependency on copied `static/` assets
- **Priority:** Important
- **Description:** The release candidate depends on copied runtime assets, so missing output files can cause reviewer friction.
- **Affected Component:** Runtime assets
- **Assigned Owner:** Ridhwaan
- **Expected Disposition:** verify before final release
- **Status This Week:** in progress
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 5. Limited operator-facing diagnostics
- **Priority:** Important
- **Description:** The prototype has local logs and test output, but maintainer-facing troubleshooting is still lighter than a production system.
- **Affected Component:** Operations / maintenance
- **Assigned Owner:** David
- **Expected Disposition:** improve before final release
- **Status This Week:** in progress
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 6. Windows-first execution path
- **Priority:** Important
- **Description:** The main release candidate is Windows-first, which limits portability and reviewer flexibility.
- **Affected Component:** Build / platform support
- **Assigned Owner:** Grey
- **Expected Disposition:** document clearly; broader portability deferred
- **Status This Week:** accepted constraint
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 7. GUI/API documentation consistency
- **Priority:** Important
- **Description:** The repo contains both a Windows GUI and a local HTTP API, so documentation must stay honest about what is integrated and what is still partial.
- **Affected Component:** API / interface docs
- **Assigned Owner:** Ridhwaan
- **Expected Disposition:** finalize before final release
- **Status This Week:** in progress
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 8. Reviewer startup friction
- **Priority:** Important
- **Description:** Reviewers may still need a more obvious launch path, runtime asset checklist, and expected healthy-state guidance.
- **Affected Component:** Runbook / onboarding docs
- **Assigned Owner:** David
- **Expected Disposition:** close in Week 15
- **Status This Week:** improved
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## 9. Packaging and final presentation polish
- **Priority:** Optional
- **Description:** The project runs locally, but final presentation packaging can still be cleaner and easier to demo.
- **Affected Component:** Delivery polish
- **Assigned Owner:** Grey
- **Expected Disposition:** if time allows in Week 15 or Week 16
- **Status This Week:** not started
- **Related PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## Issues Closed This Week
List issues or cleanup items that were completed this week and link the PRs.

- Closed item 1: Added the Week 14 release candidate summary and formal release evidence package — https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46
- Closed item 2: Added the verified runbook, user guide, and admin guide for reviewer and maintainer use — https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46
- Closed item 3: Added interface documentation, repo alignment updates, and README reviewer-path cleanup — https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## Final Note
This triage list is intended to support final release decision-making under time pressure. It is not a backlog dump. Remaining items here are the highest-value issues affecting final release confidence.