# Midterm Technical Snapshot

## Architecture Overview
The MVP consists of a C++ backend service that exposes HTTP endpoints for the application workflow.  
The system runs locally and uses in-memory storage for prototype functionality.

## Implemented Features
- C++ HTTP server
- Health endpoint
- Student creation endpoint
- Assessment submission endpoint
- Recommendation retrieval
- Static frontend page
- Automated tests
- CI pipeline validation

## Missing Features (Beta Scope)
- Persistent database storage
- Authentication and access control
- Teacher performance dashboard
- Production deployment configuration
- Improved recommendation logic

## Running the System
Follow the README instructions.

Example commands:

cmake -S . -B build  
cmake --build build

Run the application and test the endpoints locally.

## Test Status
Automated tests verify:
- health endpoint functionality
- recommendation behavior
- validation logic

Tests run using CTest as part of the CI pipeline.

## CI Status
The CI pipeline automatically verifies that the code is properly formatted, successfully builds the project, and runs the automated tests. These checks ensure that any new changes meet the project's quality standards before they are merged into the main branch.