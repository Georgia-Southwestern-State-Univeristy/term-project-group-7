# User Guide

## Who This Guide Is For
This guide is for a student, evaluator, or reviewer using the current release candidate of the math learning prototype.

## What the System Does
The system provides a focused middle-school math practice workflow through a Windows desktop GUI.

A user can:
- choose a grade level
- choose a math operation
- answer practice questions
- receive immediate feedback
- request hints
- move through a short practice session
- open the analytics view

## Main Tasks the User Can Perform
- open the application
- choose a grade level
- choose an operation
- answer questions
- receive correctness feedback
- request hints
- move to the next question
- review the analytics screen

## How To Use the System

### 1. Launch the application
Start the built executable:

```powershell
.\build\Debug\server.exe
```

### 2. Choose a grade level
Use the grade selection control on the main menu.

### 3. Choose an operation
Select one of the available practice modes:
- addition
- subtraction
- multiplication
- division

### 4. Answer a question
Read the displayed question and enter an answer in the input field.

### 5. Submit the answer
Use the submit action to check the answer.

Expected behavior:
- valid answers are checked immediately
- incorrect answers receive feedback
- invalid or missing input should not crash the application

### 6. Use a hint if needed
Select the hint option to receive guided help for the current question.

### 7. Continue to the next question
After feedback is shown, continue through the practice flow.

### 8. Open analytics
Use the analytics option from the main menu to review the available local analytics summary.

## Known Limitations
- the current release candidate is Windows-first
- the system is a local semester prototype
- the project demonstrates a focused vertical slice rather than a full production platform
- runtime success depends on local copied assets such as `questions.db`
- advanced production features such as hosted deployment, accounts, and large-scale analytics are outside the current release candidate scope

## Troubleshooting
### The application does not open
Check that the project built successfully and that you are launching `.\build\Debug\server.exe`.

### Questions do not appear
Check that `questions.db` exists inside `.\build\Debug\`.

### Analytics appears empty
If no sessions have been recorded yet, analytics may show little or no activity.

### The system behaves unexpectedly
Record the issue and refer the maintainer to `docs/admin-guide.md` and `docs/final/week14-triage.md`.