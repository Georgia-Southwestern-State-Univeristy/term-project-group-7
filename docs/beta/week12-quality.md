# Week 12 Quality Evidence

## 1. Testing Coverage

The following system paths are tested:

- CLI menu navigation
- Problem generation (addition, subtraction)
- Input validation (invalid integer handling)
- Correct/incorrect answer evaluation

## 1.1 Test Count by Type

- Unit tests: 4
- Integration tests: 0
- End-to-end tests: 0

---

## 2. Example Test Cases

| Feature | Test Case | Expected Result |
|--------|----------|---------------|
| Addition | 2 + 2 | 4 |
| Input Validation | "abc" | Error message |
| Exit Flow | Option 0 | (Known issue) requires Ctrl+C |

---

## 2.1 Tests Added This Week (Week 12)

- Added test for input validation with non-numeric values
- Added test for correct answer evaluation in addition workflow

These tests improve confidence in core CLI interactions and reduce risk of regression in user input handling.

---

## 3. CI Evidence

Latest successful run:  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/actions/runs/23611166317

---

## 4. Error Handling Evidence

The system handles:
- invalid numeric input
- incorrect answers
- menu navigation errors

---

## 4.1 Workflow Protection

The following real workflows are protected by tests:

- Selecting an operation → solving a problem → receiving feedback
- Entering invalid input → system rejects and continues safely

This ensures the main user interaction loop remains stable under normal usage.

---

## 5. Gaps in Quality

- No automated UI tests
- No persistence testing
- Limited edge case coverage

---

## 6. Persistence Coverage Status

The current Beta does not implement persistence. User progress and results are not saved after program exit.

### Planned Improvement
- Save results to a file
- Track user progress between sessions

---

## 7. Authentication Coverage Status

The current Beta does not include authentication or role-based access.

### Planned Improvement
- Add login system
- Support student/teacher roles

---

## 8. Confidence Statement

The system is stable for CLI-based workflows and supported by CI and testing evidence, but requires expansion in persistence and authentication to reach full product readiness.