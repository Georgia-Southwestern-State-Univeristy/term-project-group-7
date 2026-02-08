# Term Project Group 7

## Overview
This project demonstrates a minimal end-to-end **thin vertical slice** that proves the system runs.
The goal is execution and workflow discipline, not feature completeness.

The application serves a simple web page (`/`) and exposes a backend health endpoint (`/api/health`) to confirm the system is functioning end-to-end.

---

## Tech Stack
- **C++17**
- **CMake**
- **cpp-httplib** (single-header HTTP server/client)
- **CTest** (automated tests)
- **GitHub Actions (CI)**

---

## Project Layout
- `src/server.cpp` — C++ HTTP server (serves `/` and `/api/health`)
- `static/` — static assets (if used by the server)
- `tests/test_health.cpp` — C++ test (self-contained health check)
- `CMakeLists.txt` — build + test configuration
- `.clang-format` — formatting rules
- `.github/workflows/ci.yml` — CI pipeline (format check + build + test)

---

## Prerequisites (Windows)
Install:
- **Visual Studio 2022+** with **Desktop development with C++**
- **Developer PowerShell for Visual Studio** (installed with Visual Studio)
- **CMake**
- **clang-format** (typically included with Visual Studio/LLVM tools)

Verify in **Developer PowerShell for VS**:
```powershell
cmake --version
where.exe clang-format
clang-format --version