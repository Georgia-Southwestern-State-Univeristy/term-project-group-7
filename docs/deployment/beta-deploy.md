# Beta Deployment / Reproducible Run Path

## Goal
Provide a reproducible local run path so another person can build, run, and evaluate the Beta with minimal guessing.

---

## Run Path Type
This Beta uses a local CLI-based run path.

There is no public hosted deployment or browser-based interface for the current Beta.

---

## Environment Requirements

### Windows (recommended)
- Windows 10 or 11
- Visual Studio (with Desktop development with C++ workload installed)
- CMake (included with Visual Studio or installed separately)
- Git

---

## Environment Variables
No environment variables are required for this Beta.

---

## Database / Setup Steps
No database setup is required.

The application runs entirely in memory.

---

## Seed Data / Test Accounts
No login or test accounts are required.

The reviewer can interact with the system immediately after launch.

---

## Exact Setup Instructions

### Step 1: Clone the repository
Open PowerShell and run:

git clone https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7.git  
cd term-project-group-7

---

### Step 2: Create build directory

mkdir build  
cd build

---

### Step 3: Generate build files with CMake

cmake ..

---

### Step 4: Build the project

cmake --build .

---

### Step 5: Run the application

./app

---

## First Steps After Launch

1. Select an operation (Addition, Subtraction, Multiplication, or Division)
2. Choose a problem type (integers, decimals, etc.)
3. Solve the generated problem
4. Observe validation and feedback behavior
5. Try entering invalid input to confirm error handling

---

## Expected Behavior

- The application launches into a CLI menu
- The user selects an operation
- A math problem is generated
- The user inputs an answer
- The system evaluates correctness and provides feedback
- Invalid inputs are handled without crashing

---

## Known Limitations During Deployment

- The application must be stopped using Ctrl + C (only if 0 does not work)
- No persistence: data is not saved between runs
- No authentication or user accounts
- CLI-only interface (no browser support)

---

## Evidence of Successful Run Path

This run path has been tested locally by the team.

Recent passing CI run:
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/actions/runs/23611166317

The system builds successfully and runs as expected using the above steps.