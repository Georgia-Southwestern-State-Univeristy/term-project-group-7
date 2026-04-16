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
Document any real failures found while another team member followed this runbook.

### Failure 1
- **Problem:** NEED TO INSERT
- **Cause:** NEED TO INSERT
- **Fix:** NEED TO INSERT
- **PR:** NEED TO INSERT

### Failure 2
- **Problem:** NEED TO INSERT
- **Cause:** NEED TO INSERT
- **Fix:** NEED TO INSERT
- **PR:** PR LINK

## Corrections Made After Verification
List what was corrected in either the docs or the system after someone else followed the run path.

- Correction 1: NEED TO INSERT
- Correction 2: NEED TO INSERT

## Verification Evidence
- Verifier: David
- Verification date: 4/16/2026
- Related PR: PR LINK
- Related issue: ISSUE LINK
- CI run: ACTIONS RUN LINK
- Screenshot(s): SCREENSHOT LINK

## Final Result
The release candidate run path is:
- documented
- repeatable
- testable
- reviewable without hidden setup knowledge

Any remaining gaps are tracked in `docs/final/week14-triage.md`.