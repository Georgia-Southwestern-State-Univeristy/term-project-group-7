# Term Project Group 7

## Overview
This project demonstrates a minimal end-to-end **thin vertical slice** that proves the system runs.
The goal is execution and workflow discipline, not feature completeness.

The application serves a simple web page and exposes backend endpoints to confirm the system is functioning end-to-end.

- Web page: `GET /`
- Health endpoint: `GET /api/health` → returns HTTP 200

---

## Tech Stack
- C++17
- CMake (build system)
- CTest (tests)
- cpp-httplib (single-header HTTP server/client)
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