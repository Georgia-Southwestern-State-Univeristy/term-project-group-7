# Term Project Group 7

## Overview
This project is a focused **thin vertical slice** prototype for a middle-school math learning system.

The current release candidate demonstrates:
- a runnable **Windows desktop application** built in C++ with a Win32 GUI
- local SQLite-backed question content and analytics data
- a local HTTP API for the project’s documented interface layer
- automated tests for regression, validation, and rules behavior

The project is intentionally limited in scope to remain feasible within a single semester. The goal is to prove that the system can be built, run, verified, maintained, and reviewed in a disciplined way.

## Release Candidate Scope
The current release candidate includes:
- grade selection from the main menu
- operation selection for practice workflows
- question delivery and answer submission
- hint support during practice
- analytics viewing inside the GUI
- local HTTP health/API endpoints
- automated regression and validation tests
- release, runbook, user, admin, and interface documentation

## Tech Stack
- C++17
- CMake
- CTest
- Win32 GUI
- SQLite
- cpp-httplib
- GitHub Actions
- clang-format

## Supported Environment
### Recommended
- Windows 10 or Windows 11
- Visual Studio 2022 with **Desktop development with C++**
- Developer PowerShell for Visual Studio
- CMake
- Git

### Notes
This repository is primarily set up for the Windows build path. The main release candidate executable is the Windows target `server`.

## Repository Layout
- `CMakeLists.txt`
- `README.md`
- `questions.db`
- `database/`
  - `schema.sql`
  - `seed_questions.sql`
  - `sqlite/`
- `docs/`
  - `api/`
    - `openapi.yaml`
    - `interface-overview.md`
  - `deployment/`
    - `beta-deploy.md`
  - `final/`
    - `week14-runbook.md`
    - `week14-triage.md`
    - `week14-repo-polish.md`
  - `releases/`
    - `release-candidate.md`
  - `admin-guide.md`
  - `user-guide.md`
- `include/`
- `src/`
- `static/`
- `tests/`

## Build
Run these commands from the repo root in **Developer PowerShell for Visual Studio**:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

## Run
After building, launch the Windows executable:

```powershell
.\build\Debug\server.exe
```

The build copies required runtime assets into the executable output folder, including:
- `questions.db`
- `static/`

Expected behaviors after launch:
- the main GUI window opens
- grade selection is visible
- operation buttons are visible
- question flow can be started
- analytics can be opened
- the local health endpoint is available at `http://127.0.0.1:5000/api/health`

## Testing
Run the test suite with:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

Detailed startup and verification steps are documented in `docs/final/week14-runbook.md`.

## Where a Reviewer Should Start
1. `README.md`
2. `docs/releases/release-candidate.md`
3. `docs/final/week14-runbook.md`
4. `docs/user-guide.md`
5. `docs/admin-guide.md`
6. `docs/api/interface-overview.md`
7. `docs/api/openapi.yaml`
8. `tests/`

## Key Documentation
- Release candidate summary: `docs/releases/release-candidate.md`
- Runbook verification: `docs/final/week14-runbook.md`
- User guide: `docs/user-guide.md`
- Admin / maintenance guide: `docs/admin-guide.md`
- API contract: `docs/api/openapi.yaml`
- Interface overview: `docs/api/interface-overview.md`
- Final bug triage: `docs/final/week14-triage.md`
- Repo polish summary: `docs/final/week14-repo-polish.md`

## Known Limitations
- The release candidate is Windows-first
- The project remains a semester prototype, not a production deployment
- The GUI workflow and HTTP API are both present, but not yet unified into a full production-style platform
- Runtime success depends on copied local assets such as `questions.db`
- Operational diagnostics are local and lightweight rather than production-grade

## Release Status
This repository is being prepared as a formal release candidate prior to final release.

See `docs/releases/release-candidate.md` for the current release summary, known risks, and remaining work.