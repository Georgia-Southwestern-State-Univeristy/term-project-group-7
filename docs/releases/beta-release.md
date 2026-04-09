# Beta Release Notes

## Release Name and Tag
**Release name:** Beta v0.1  
**Git tag:** `beta-v0.1`

## Release Date
March 2026

## Beta Summary
This Beta release delivers a runnable CLI-based math practice application written in C++. The system can be built locally, launched from the command line, and evaluated by another reviewer through a menu-driven workflow.

## Major Included Features and Workflows

### 1. CLI-based math workflow
The application launches into an interactive terminal menu where the user can choose:

- Addition
- Subtraction
- Multiplication
- Division

### 2. Problem type selection
Within each operation, the user can select problem categories such as:

- Integers
- Decimals
- Fractions
- Mixed

### 3. Immediate answer feedback
The application evaluates user input and reports whether the answer is correct or incorrect.

### 4. Input validation
If the user enters invalid input where an integer is expected, the program displays a validation message such as:

`Please enter a valid integer`

### 5. Automated tests and CI
The repository includes automated test executables and a GitHub Actions CI workflow to support Beta confidence.

## Important Fixes / Improvements Since Weeks 10–11
- clearer Week 12 deployment/run-path documentation
- README updated to match the actual runnable CLI application
- Beta documentation aligned to the current implementation instead of a browser-based workflow
- CI/test evidence consolidated into Week 12 documentation
- known issues documented more honestly, including current exit behavior

## Known Limitations Still Present
- the application is CLI-only and does not provide a browser interface
- the app currently requires `Ctrl + C` to fully stop after menu exit behavior instead of closing cleanly on `0`
- there is no persistent storage, so user progress is not saved
- there is no authentication or role-based access implemented
- there is no public/live deployment link
- repo contents include broader test and documentation artifacts beyond the currently demonstrated CLI Beta path

## Release Evidence
**GitHub release page / artifact:**  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/releases/tag/beta-v0.1

**Project repository:**  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7

**Recent passing CI run:**  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/actions/runs/23611166317

## Beta Release Judgment
This Beta is credible because another reviewer can clone the repo, build it, run the CLI application, and evaluate a real workflow with test and CI evidence. It is not yet a polished final release, but it is runnable, reviewable, and documented honestly.