# Hand-Off Document (Final Draft)

## Purpose

This document allows a reviewer, future developer, or evaluator to understand, run, and extend the project without needing prior team knowledge.

---

## System Overview

This project is a semester-scale adaptive learning platform prototype focused on a thin vertical slice for middle-school math.

The system demonstrates:

* Windows desktop application (C++ Win32 GUI)
* SQLite-based local data storage
* Lightweight HTTP API
* Automated testing and CI
* Complete documentation for setup and usage

---

## Architecture Overview

### Interfaces

1. Windows GUI
2. Local HTTP API

### Core Flow

User → GUI → Question Engine → Evaluation → Feedback → Analytics

### Features

* Grade selection
* Math problem generation
* Answer validation
* Hint system
* Analytics display
* Health endpoint

### Important Note

This is a prototype. GUI and API coexist but are not fully unified.

---

## Technology Stack

* C++17
* Win32 GUI
* CMake
* SQLite
* cpp-httplib
* CTest
* GitHub Actions

---

## Repository Structure

### Core

* src/server.cpp
* src/gui/

### Data

* questions.db
* database/

### Docs

* README.md
* docs/

---

## Setup / Run Instructions

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

Ensure the following exist in:

.\build\Debug\

* server.exe
* questions.db
* static/

---

## Health Check

http://127.0.0.1:5000/api/health

Expected:
{"status":"ok","service":"cpp"}

---

## Known Issues

* Windows-only
* Requires manual runtime files
* GUI + API not fully integrated
* Not production-ready

---

## Recommended Next Steps

1. Unify architecture
2. Improve deployment
3. Add logging
4. Improve UX
5. Expand scalability

---

## Documentation References

* README.md
* docs/user-guide.md
* docs/admin-guide.md
* docs/api/

---

## Final Assessment

This project is a working academic prototype that is buildable, runnable, testable, and reviewable.
