# Week 15 Final QA Checklist + Demo Path Verification

## Purpose
This document records the final QA pass for Week 15 and verifies the exact demo path the team plans to use during the final presentation. The goal is not only to show that the project can start, but also to show how it behaves during core workflow execution and when common failure conditions occur.

---

## Verification Environment

- OS: Windows 10/11
- Shell: Developer PowerShell for Visual Studio
- IDE/Toolchain: Visual Studio 2022 with Desktop development with C++
- Build System: CMake
- Test Runner: CTest
- Runtime Style: local Windows desktop execution with copied runtime assets

---

## Build and Verification Commands

### 1. Configure
```powershell
cmake -S . -B build
```

### 2. Build
```powershell
cmake --build build --config Debug
```

### 3. Run tests
```powershell
ctest --test-dir build -C Debug --output-on-failure
```

### 4. Launch
```powershell
.\build\Debug\server.exe
```

---

## Final QA Checklist

### A. Startup / Deployment Verification
- [ ] CMake configure succeeds without blocking errors
- [ ] Debug build completes successfully
- [ ] CTest completes without failing tests
- [ ] `server.exe` is produced in `.\build\Debug\`
- [ ] required runtime files are present before launch
- [ ] application starts without immediate crash or missing-file failure

### B. Runtime Asset Verification
- [ ] `questions.db` exists in `.\build\Debug\`
- [ ] `static/` exists in `.\build\Debug\`
- [ ] runtime launch does not fail because of missing local assets

### C. Core Workflow Verification
- [ ] main menu opens correctly
- [ ] grade selection can be made successfully
- [ ] operation selection starts a question session
- [ ] a valid answer can be submitted successfully
- [ ] hint functionality can be shown during question flow
- [ ] next-question flow continues without blocking
- [ ] analytics view opens without crashing

### D. API / Access Verification
- [ ] `GET /api/health` returns a healthy response
- [ ] the local health endpoint can be shown during the demo

### E. Error-Handling / Failure Verification
- [ ] startup risk from missing runtime assets is understood and checked before demo
- [ ] the team can explain what breaks if `questions.db` is missing
- [ ] the team can explain what breaks if `static/` is missing
- [ ] the team can explain the difference between successful runtime flow and blocked startup/runtime conditions
- [ ] the presentation backup plan covers partial demo failure

---

## Exact Demo Path (Final Presentation)

### Primary Live Demo Path
1. Open the built application from the verified runtime location.
2. Show the main menu and confirm the app starts cleanly.
3. Select a grade level.
4. Choose a math operation.
5. Start a question session.
6. Answer one question correctly to show normal progress.
7. Answer one question incorrectly to show normal incorrect-answer handling.
8. Show the hint feature.
9. Move to the next question.
10. Open analytics to show that the session flow is connected to visible runtime behavior.
11. Open a browser and visit `http://127.0.0.1:5000/api/health`.
12. Confirm the health endpoint responds successfully.

### Demo Notes
- The team will use a rehearsed, low-risk path rather than improvising.
- Runtime dependencies will be checked before the final presentation begins.
- The demo is intended to show both functionality and operational readiness.

---

## Failure Scenarios Reviewed for Final Readiness

### Missing `questions.db`
- Risk: question flow may fail or the runtime path may be incomplete
- Handling: verified before demo
- Mitigation: ensure file exists before launch

### Missing `static/`
- Risk: UI or runtime assets fail to load
- Handling: verified before demo
- Mitigation: ensure folder exists before launch

### Reviewer Setup Confusion
- Risk: incorrect setup prevents execution
- Handling: guided by README + QA doc
- Mitigation: consistent documented commands

### Partial Demo Failure
- Risk: demo does not fully work live
- Handling: switch to explanation + backup plan
- Mitigation: rehearsed fallback plan

---

## Rehearsal Results

### What Worked
- build/test/run pipeline executed successfully
- demo path is stable and repeatable
- GUI workflow functions as expected
- health endpoint responds correctly
- runtime dependencies identified clearly

### What Was Confusing
- dependency on local runtime files
- GUI and API separation in system design
- some documentation wording needed clarity

### What Was Fixed
- clarified runtime requirements
- improved QA documentation depth
- aligned presentation + QA + handoff wording
- ensured demo path is controlled and realistic

---

## Evidence

- Week 14 PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46
- Week 15 PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/48

---

## Final QA Assessment

The project is considered final-ready if:
- it builds successfully
- runtime assets are present
- demo path works end-to-end
- failure cases are understood and explainable
- backup plan is ready

---

## Verification

- Verified by: Victor Grey
- Date: 04/20/2026
- PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/48