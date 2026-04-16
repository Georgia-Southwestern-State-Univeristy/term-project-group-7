# Week 14 Runbook Verification

## Purpose
This runbook proves that the release candidate can be built, launched, and verified by following documented steps rather than relying on hidden team knowledge.

## Environment Used for Verification
- OS: Windows 10/11
- Shell: Developer PowerShell for Visual Studio
- IDE/Toolchain: Visual Studio 2022 with Desktop development with C++
- Build System: CMake
- Version Control: Git

## Required Dependencies
- Visual Studio 2022 with **Desktop development with C++**
- CMake
- Git

## Repository Preparation
Clone the repository and open **Developer PowerShell for Visual Studio** in the repository root.

```powershell
git clone https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7
cd term-project-group-7
```

## Exact Startup Steps

### 1. Configure the build
```powershell
cmake -S . -B build
```

### 2. Build the project
```powershell
cmake --build build --config Debug
```

### 3. Run the automated tests
```powershell
ctest --test-dir build -C Debug --output-on-failure
```

### 4. Verify runtime assets
Confirm that the output folder contains:
- `server.exe`
- `questions.db`
- the copied `static/` directory

Expected Windows output path:

```powershell
.\build\Debug\
```

If `questions.db` is missing from the runtime output folder, the GUI question flow and analytics features may not behave correctly.

### 5. Launch the application
Run:

```powershell
.\build\Debug\server.exe
```

Expected startup behavior:
- the desktop application window opens
- the main menu is visible and interactive
- the local service is reachable on `http://127.0.0.1:5000`

## Health Verification Checklist

### GUI verification
- [ ] main menu opens
- [ ] grade selection is visible
- [ ] operation buttons are visible
- [ ] a practice workflow can be started
- [ ] submit behavior works
- [ ] hint behavior works
- [ ] next-question flow works
- [ ] analytics window opens
- [ ] application remains stable during a short session

### Runtime asset verification
- [ ] `questions.db` exists in `.\build\Debug\`
- [ ] `static\` exists in `.\build\Debug\`
- [ ] no immediate startup failure occurs because of missing local assets

### HTTP verification
Open a browser and visit:

`http://127.0.0.1:5000/api/health`

Expected result:

```json
{"status":"ok","service":"cpp"}
```

## Database / Seed Notes
This project uses a local SQLite database file:
- runtime DB file: `questions.db`
- schema reference: `database/schema.sql`
- seed reference: `database/seed_questions.sql`

The runtime build path depends on `questions.db` being copied into the executable output directory.

## Failure Cases Observed During Verification
No blocking runbook failures were recorded during this verification cycle. The main value of verification was confirming the exact startup path, runtime asset expectations, and reviewer-facing documentation.

### Failure 1
- **Problem:** The original run path was not explicit enough about checking for `questions.db` in the runtime output directory.
- **Cause:** The project depends on runtime-local assets, and that dependency was easy to miss if a reviewer only followed build steps.
- **Fix:** The runbook was updated to explicitly verify `questions.db` in `.\build\Debug\` before launch.
- **PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

### Failure 2
- **Problem:** The expected healthy-state verification steps were too implicit for a reviewer who did not already know the project.
- **Cause:** Earlier documentation assumed the reviewer would already know to check the GUI flow and `http://127.0.0.1:5000/api/health`.
- **Fix:** The runbook now includes a GUI checklist, runtime asset checklist, and HTTP health verification section.
- **PR:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46

## Corrections Made After Verification
- Correction 1: Added explicit runtime asset verification for `questions.db` and `static/`.
- Correction 2: Added a clearer healthy-state checklist for GUI startup and HTTP verification.

## Verification Evidence
- Verifier: David
- Verification date: 4/16/2026
- Related PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/46
- Related issue: None. This verification work was tracked directly in PR #46.
- CI run: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/actions/runs/24242221810
- Screenshot(s): Verification was documented directly in this file and in PR #46.

## Final Result
The release candidate run path is:
- documented
- repeatable
- testable
- reviewable without hidden setup knowledge

Any remaining gaps are tracked in `docs/final/week14-triage.md`.