# Interface Overview

## Purpose
This document explains the major interfaces in the current release candidate so another developer can understand how the system is used and where to extend it.

## Current Interface Model
The current repository exposes two visible interface layers:

1. **Primary user-facing interface:** Windows desktop GUI
2. **Secondary system interface:** local HTTP API

## Important Clarification
The GUI workflow and the HTTP API both exist in the current release candidate and are launched from the same executable, but they are not yet a fully unified production-style platform. This document describes the interfaces honestly as they exist today.

## Primary User-Facing Interface
The main release candidate experience is the Windows desktop application.

### Major user-facing modules
- main menu
- grade selection
- operation selection
- question workflow
- hint flow
- answer submission
- analytics view

### Primary source areas
- `src/gui/main_menu_gui.cpp`
- `src/gui/addition_gui.cpp`
- `src/gui/analytics_gui.cpp`
- `src/gui/question_bank.cpp`

## Secondary System Interface
The project also exposes a local HTTP API in `src/server.cpp`.

### Current documented routes
- `GET /`
- `GET /api/health`
- `POST /api/students`
- `POST /api/students/{studentId}/assessments`
- `GET /api/students/{studentId}/recommendations/latest`
- `POST /api/students/{studentId}/teacher-override`

The formal API contract is documented in `docs/api/openapi.yaml`.

## Data and Storage
The current repo uses:
- `questions.db` for local SQLite-backed question and analytics data used by the GUI workflow
- `src/in_memory_store.h` for in-memory API state used by the MVP service layer

This split should be documented clearly instead of pretending the whole system is already unified.

## How Another Developer Can Extend It

### To extend the GUI
Work in:
- `src/gui/`
- `include/gui/`
- related docs
- related tests where applicable

### To extend the HTTP API
Work in:
- `src/server.cpp`
- `src/mvp_service.h`
- `src/in_memory_store.h`
- `docs/api/openapi.yaml`
- tests covering updated behavior

### To extend local data behavior
Work in:
- `database/schema.sql`
- `database/seed_questions.sql`
- `questions.db`
- question-bank-related source files

## Rule for Documentation
The implementation and the interface documentation must stay aligned.  
“See the code” alone is not sufficient interface documentation for this project.