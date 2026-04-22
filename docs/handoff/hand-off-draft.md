# Hand-Off Document (Near-Final Draft)

## Purpose
This document is intended to help a reviewer, teammate, or future maintainer understand what the project is, how to run it, what to expect from it, what its current limits are, and what should happen next if development continues.

---

## System Overview
This project is a semester-scale adaptive learning platform prototype focused on a thin vertical slice for middle-school math. The team prioritized a buildable, runnable, and reviewable prototype over full production scope.

The current project demonstrates:
- a Windows desktop application built in C++
- a local runtime model that depends on packaged assets
- SQLite-backed question/runtime data
- a lightweight local HTTP health endpoint
- automated build/test support through CMake, CTest, and CI
- repo documentation intended to support review, setup, and hand-off

---

## Architecture Snapshot

### Main Interfaces
1. Windows GUI
2. Local HTTP API / health endpoint

### Core Runtime Flow
User interaction in the GUI leads into question flow, answer evaluation, feedback behavior, and analytics visibility.

High-level flow:
User → GUI → Question / Evaluation Flow → Feedback / Hinting → Analytics

### Current Scope Note
This is a semester prototype. The GUI and local HTTP API coexist in the repo, but they are not presented as a single fully unified production application stack.

---

## Stack Rationale
The project emphasizes a Windows-first, C++-based implementation that the team could build, explain, test, and hand off within the semester.

Key choices:
- **C++17:** aligned with the team’s final implementation direction
- **Win32 GUI:** provided a direct desktop interface for the math workflow
- **SQLite:** lightweight local data/runtime support
- **cpp-httplib:** simple local HTTP support for health verification
- **CMake + CTest:** consistent build and test workflow
- **GitHub Actions:** CI evidence for build/test automation

The technical choices favor feasibility, transparency, and reviewability over production-scale complexity.

---

## Repository Structure

### Main Areas
- `src/` - main source implementation
- `src/gui/` - GUI-related implementation
- `database/` - database-related assets/support
- `docs/` - reviewer-facing project documentation
- `.github/workflows/` - CI configuration

### Important Reviewer-Facing Documents
- `README.md`
- `docs/final/week15-qa.md`
- `docs/final/week15-presentation-plan.md`
- `docs/final/week15-handoff-status.md`
- `docs/user-guide.md`
- `docs/admin-guide.md`
- `docs/api/interface-overview.md`

---

## Setup / Build / Test / Run Summary

### Clone
```bash
git clone https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7.git
cd term-project-group-7
```

### Configure
```powershell
cmake -S . -B build
```

### Build
```powershell
cmake --build build --config Debug
```

### Test
```powershell
ctest --test-dir build -C Debug --output-on-failure
```

### Run
```powershell
.\build\Debug\server.exe
```

---

## Runtime Requirements
Before running the main executable, verify that the expected runtime files are present in:

`.\build\Debug\`

Expected runtime items include:
- `server.exe`
- `questions.db`
- `static/`

If required runtime assets are missing, startup or runtime behavior may fail or become incomplete.

---

## Verification / Health Check
Local health endpoint:

`http://127.0.0.1:5000/api/health`

Expected response:
```json
{"status":"ok","service":"cpp"}
```

This endpoint is useful as a simple technical verification point, but it should not be treated as proof that every GUI/runtime path is fully production-ready.

---

## Known Issues and Constraints

### Known Issues
- the primary execution path is Windows-first
- runtime success depends on local assets being present in the correct build output location
- the project does not provide a polished production deployment experience
- GUI flow and local API presence are not yet a fully unified end-user platform

### Constraints
- this was developed as a semester prototype with limited time and scope
- the team intentionally prioritized a thin vertical slice over broad feature completeness
- reviewer success depends on following the documented setup/run steps
- some final evidence references may still require last-pass replacement before submission

---

## Recommended Next Steps
If development continued beyond the current semester scope, the highest-value next steps would be:

1. reduce runtime setup friction and improve packaging/deployment
2. improve asset handling so required files are less manual
3. strengthen error handling and user-facing failure feedback
4. unify the system more clearly across GUI and service behavior
5. expand testing around real runtime and workflow scenarios
6. improve long-term maintainability and deployment documentation

---

## User / Admin / Interface Guidance References
Reviewers should use the following docs for additional guidance:
- `README.md`
- `docs/user-guide.md`
- `docs/admin-guide.md`
- `docs/api/interface-overview.md`

These documents provide the main reviewer path for setup, usage, and interface understanding.

---

## Final Assessment
This project should be understood as a working academic prototype: buildable, testable, reviewable, and presentable, but not production-complete. Its strongest value is that it demonstrates a real, explainable vertical slice with documented setup, visible runtime behavior, and an honest statement of limits.