# Admin / Maintenance Guide

## Purpose
This guide is for a reviewer, teammate, or maintainer who needs to build, run, diagnose, and update the current release candidate without relying on team chat knowledge.

## System Summary
The current release candidate is a Windows-first C++ prototype consisting of:
- a Win32 desktop GUI
- local SQLite-backed question content and analytics data
- a local HTTP API
- supporting runtime assets
- automated tests for regression and validation

## Required Tools
- Visual Studio 2022 with **Desktop development with C++**
- Developer PowerShell for Visual Studio
- CMake
- Git

## Build Commands
From the repo root:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

## Test Commands
```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Run Command
```powershell
.\build\Debug\server.exe
```

## Important Project Files

### Build / root
- `CMakeLists.txt`
- `README.md`

### Source / runtime
- `src/server.cpp`
- `src/gui/main_menu_gui.cpp`
- `src/gui/addition_gui.cpp`
- `src/gui/analytics_gui.cpp`
- `src/gui/question_bank.cpp`

### Data
- `questions.db`
- `database/schema.sql`
- `database/seed_questions.sql`

### Interface docs
- `docs/api/openapi.yaml`
- `docs/api/interface-overview.md`

### Tests
- `tests/`

## Runtime Expectations
The build copies runtime assets into the executable output directory:
- `questions.db`
- `static/`

Expected Windows output path:

```powershell
.\build\Debug\
```

## Healthy State Checklist
A healthy local state should meet all of the following:
- CMake configure succeeds
- the project builds successfully
- tests pass
- `.\build\Debug\server.exe` launches successfully
- the main GUI is usable
- `questions.db` exists in `.\build\Debug\`
- `static\` exists in `.\build\Debug\`
- `http://127.0.0.1:5000/api/health` returns `{"status":"ok","service":"cpp"}`

## Restart Procedure
1. close the running application
2. rebuild if source changes were made
3. relaunch `.\build\Debug\server.exe`

## Recovery Procedures

### If the build folder becomes inconsistent
```powershell
Remove-Item -Recurse -Force build
cmake -S . -B build
cmake --build build --config Debug
```

### If `questions.db` is missing at runtime
- confirm `questions.db` exists at the repository root
- confirm the post-build copy placed `questions.db` in `.\build\Debug\`
- rebuild the project

### If `static\` is missing at runtime
- rebuild the project
- confirm the post-build copy step ran successfully

### If tests fail
Run:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

Then inspect the related file under `tests/`.

## Diagnostics

### Build diagnostics
Build errors appear in:
- Developer PowerShell output
- Visual Studio build output

### Test diagnostics
Test failures appear in:
- CTest terminal output

### Runtime / HTTP diagnostics
The local service logs requests and errors through the running process output.

## Interface Notes
The current repo contains both:
- a Windows GUI practice interface
- a local HTTP API interface

They coexist in the same executable, but they are not yet a fully unified production platform. Documentation should stay honest about that.

## How To Extend the System
A maintainer should start with:
1. `README.md`
2. `docs/api/interface-overview.md`
3. `docs/api/openapi.yaml`
4. `src/server.cpp`
5. relevant GUI source files
6. related tests

## Current Maintenance Risks
- runtime asset copying is required for successful startup
- documentation must stay aligned with the real build/run path
- Windows-first assumptions should be called out clearly
- interface docs and implementation must be updated together`