# Week 15 Final QA Checklist + Demo Path Verification

## Purpose

This document records the final QA pass performed during Week 15 and verifies the exact demo path the team will use during the final presentation.

---

## Verification Environment

* OS: Windows 10/11
* Shell: Developer PowerShell for Visual Studio
* IDE/Toolchain: Visual Studio 2022 with Desktop development with C++
* Build System: CMake
* Version Control: Git

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

### Build / Startup Checks

* [ ] CMake configure succeeds
* [ ] Debug build completes successfully
* [ ] All tests pass successfully
* [ ] server.exe exists in .\build\Debug\

### Runtime Asset Checks

* [ ] questions.db exists in .\build\Debug\
* [ ] static/ exists in .\build\Debug\
* [ ] Application launches without missing-file errors

### GUI Workflow Checks

* [ ] Main menu loads correctly
* [ ] Grade selection works
* [ ] Operation buttons are clickable
* [ ] Question session starts successfully
* [ ] Answer submission works
* [ ] Hint functionality works
* [ ] Next question flow works
* [ ] Analytics view opens correctly
* [ ] No crashes during interaction

### HTTP Endpoint Checks

* [ ] http://127.0.0.1:5000/api/health returns {"status":"ok","service":"cpp"}

---

## Exact Demo Path (Final Presentation)

1. Launch application
2. Show main menu
3. Select grade level
4. Choose a math operation
5. Answer one question correctly
6. Answer one question incorrectly
7. Show hint functionality
8. Move to next question
9. Open analytics
10. Open browser and verify health endpoint

---

## Rehearsal Results

### What Worked

* Build process completed successfully
* Application launched without errors
* GUI workflow was stable
* Demo path executed without blocking issues
* Health endpoint responded correctly

### What Was Risky or Confusing

* Runtime depends on questions.db and static/ being present
* GUI and HTTP API are not fully unified
* Some earlier documentation required cleanup

### What Was Fixed

* Updated hand-off document
* Finalized presentation structure
* Created contribution documentation
* Clarified remaining work

---

## High Priority Fixes / PRs

* Week 14 PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46
* Week 15 PR: WEEK 15 PR LINK

---

## Final QA Result

The project is final-ready if:

* Build works
* Demo path works
* Runtime files exist
* Documentation is consistent

---

## Verification Evidence

* Verified by: Victor Grey
* Date: 04/20/2026
* PR: WEEK 15 PR LINK
