# Week 13 Refactoring + Code Health Improvements

## Technical Debt Areas Identified

### 1. Validation logic was scattered across service methods
**Problem:**  
The service repeated validation checks in multiple methods for student creation, assessment submission, and teacher override flow. This increased duplication and made future changes riskier.

**Why it was a problem:**  
When validation rules are spread across multiple methods, maintainers must update several places to keep behavior consistent. That makes the code easier to break and harder to review.

### 2. Student existence checks were repeated
**Problem:**  
Multiple service methods performed their own student lookup and error handling.

**Why it was a problem:**  
This repeated the same responsibility and made the service less clear. It also increased the chance of inconsistent error behavior across methods.

## Refactor Completed This Week

### Refactored Area
`src/mvp_service.h`

### What changed
The service was refactored to move repeated logic into dedicated helper methods:
- `require_student(...)`
- `validate_student_input(...)`
- `validate_assessment_input(...)`
- `validate_teacher_override_input(...)`
- `build_rule_recommendation(...)`

### Why this is better
- Validation responsibilities are now centralized.
- Student lookup behavior is now handled consistently.
- Public service methods are shorter and easier to understand.
- Future rule or validation changes can be made in one place instead of several.
- The service is easier to test because behavior is more clearly separated.

## Evidence of Refactor Protection
The refactor was protected by automated tests, including:
- `tests/test_validation_teacher_override_missing_reason.cpp`
- `tests/test_refactor_assessment_missing_skill.cpp`
- existing regression and boundary tests already covering service behavior

## PR Evidence
- Refactor PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/43
- Supporting test PR or same PR: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/43