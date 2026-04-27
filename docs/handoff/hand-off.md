# Project Hand-Off Document

## System Overview

The Adaptive Learning Platform is a backend-focused system designed to evaluate student performance and generate learning recommendations using a rules-based adaptive engine. The system exposes REST API endpoints that simulate student workflows such as account creation, assessment submission, and recommendation retrieval.

This project is intended as a functional prototype demonstrating architecture, adaptive logic, CI/CD integration, and testing practices.

---

## Architecture Snapshot

The system follows a lightweight modular backend architecture:

* **Backend:** C++17 HTTP server (cpp-httplib)
* **API Layer:** REST endpoints for student workflows
* **Adaptive Engine:** Rules-based logic for recommendations
* **Database:** SQLite for persistence
* **Build System:** CMake
* **Testing:** CTest
* **CI/CD:** GitHub Actions

### Data Flow

1. Student is created via API
2. Assessment is submitted
3. System evaluates score
4. Adaptive logic determines learning path
5. Recommendation is returned

---

## Tech Stack and Rationale

### C++

Chosen for performance, control, and demonstrating lower-level system design.

### SQLite

Lightweight, file-based database suitable for local prototype development.

### CMake + CTest

Provides a standardized build and testing workflow.

### GitHub Actions

Ensures automated validation of build and test processes.

### Rules-Based Logic

Selected for simplicity and explainability instead of machine learning.

---

## Repository Structure

```plaintext
src/                → Core application logic (server.cpp)
include/            → Header files
tests/              → Unit tests
docs/               → Documentation and deliverables
build/              → Generated build files
.github/workflows/  → CI pipeline configuration
```

---

## Setup and Run Instructions

### Prerequisites

* C++17 compatible compiler
* CMake
* Git

### Build Steps

```bash
git clone <repo-url>
cd term-project-group-7

mkdir build
cd build
cmake ..
cmake --build .
ctest
```

### Run the Server

```bash
./server
```

---

## API Usage (Core Workflow)

### 1. Create Student

POST `/api/students`

### 2. Submit Assessment

POST `/api/students/{studentId}/assessments`

### 3. Retrieve Recommendation

GET `/api/students/{studentId}/recommendations/latest`

---

## Known Issues and Constraints

* No authentication or user management system
* Limited scalability (local-only deployment)
* Rule-based recommendations (no ML personalization)
* Minimal frontend/UI support
* Limited performance testing

---

## Testing and CI Evidence

* Unit tests implemented using CTest
* CI pipeline validates:

  * Successful build
  * Test execution
  * Code formatting checks

All CI runs are available via GitHub Actions.

---

## Maintenance Notes

* Follow existing directory structure when adding features
* Maintain CMake configuration for builds
* Keep tests updated with new functionality
* Ensure CI pipeline remains passing before merging changes
* Use consistent formatting (clang-format)

---

## Recommended Next Steps

### High Priority

1. Implement authentication and user roles
2. Expand adaptive logic (introduce ML-based recommendations)

### Medium Priority

3. Develop frontend interface
4. Improve API validation and error handling

### Long Term

5. Deploy system to cloud (AWS/Azure)
6. Add performance and load testing
7. Improve scalability and database design

---

## Key File Locations

* `src/server.cpp` → Main application entry point
* `include/` → Header definitions
* `tests/` → Unit testing files
* `docs/` → All documentation
* `.github/workflows/` → CI pipeline

---

## Example End-to-End Workflow

1. Send POST request to create a student
2. Submit assessment data for that student
3. System processes score and determines proficiency
4. Adaptive logic generates recommendation
5. Retrieve recommendation via API

---

## Final Notes

This system is stable and functional as a backend prototype. It demonstrates solid software engineering practices including modular design, CI/CD integration, and structured documentation.

The project is not fully production-ready but provides a strong foundation for continued development by future teams.
