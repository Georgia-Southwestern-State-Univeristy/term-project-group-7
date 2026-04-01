# Term Project Group 7

## Overview
This project demonstrates a minimal end-to-end **thin vertical slice** that proves the system runs.
The goal is execution and workflow discipline, not feature completeness.

The current Beta implementation is a **CLI-based math practice application** that demonstrates a complete runnable workflow.

Users can:
- Select a math operation (addition, subtraction, multiplication, division)
- Choose a problem type (integers, decimals)
- Solve generated problems
- Receive immediate feedback
- Experience input validation

The project is designed to evolve into a broader system (including a browser-based interface), but the current Beta is evaluated through a CLI workflow.

---

## Tech Stack
- C++17
- CMake (build system)
- CTest (tests)
- Standard C++ CLI application (no web server in current Beta)
- clang-format (formatting)
- GitHub Actions (CI)

---

## Prerequisites

### Windows (recommended for this repo)
Install:
- Visual Studio 2022/2026 (or Build Tools) with **Desktop development with C++**
- CMake
- Git

Use **Developer PowerShell for Visual Studio** (important).

### macOS / Linux (optional)
Install:
- A C++ compiler (clang or g++)
- CMake
- Git
- clang-format

---

## Build (from repo root)

> IMPORTANT: On Windows, run these commands in **Developer PowerShell for Visual Studio**.

```powershell
cmake -S . -B build
cmake --build build --config Debug