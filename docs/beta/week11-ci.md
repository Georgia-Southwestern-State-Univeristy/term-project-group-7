# Week 11 Testing + CI Stability

## Goal
Ensure the primary workflow is protected by meaningful automated tests and validated through CI.

---

## Current CI Pipeline

Located in:
`.github/workflows/ci.yml`

Pipeline stages:
- repository checkout
- clang-format validation
- CMake configuration
- build
- test execution (CTest)

---

## Core Workflow-Protecting Tests

### 1. Happy Path Test
`test_happy_high_score_rules.cpp`
- verifies correct recommendation for high scores

### 2. Boundary Test
`test_boundary_score_70_cutoff.cpp`
- verifies rule cutoff at score 70

### 3. Failure Path Test
`test_failure_invalid_score.cpp`
- ensures invalid scores are rejected

### 4. Regression Test
`test_regression_unknown_student_recommendation.cpp`
- ensures safe handling of missing students

---

## Additional Supporting Tests

- `test_mvp_service.cpp`
- `test_health.cpp`
- `test_auth_teacher_override_authorized.cpp`
- `test_auth_teacher_override_unauthorized.cpp`
- `test_validation_teacher_override_missing_reason.cpp`

---

## Coverage Summary

The system includes:
- workflow validation tests
- boundary condition tests
- failure handling tests
- regression protection

These tests protect actual system behavior, not just isolated functions.

---

## Important Honesty Note

The Week 11 requirement specifies adding new tests.

The current repository already contains a strong set of tests. While they clearly protect the workflow, the repository snapshot alone does not prove all were newly added in Week 11.

To fully satisfy this requirement, the Week 11 PR should include:
- newly added tests OR
- clearly updated/extended tests

---

## CI Stability Notes (UPDATED FROM FEEDBACK)

CI currently verifies:
- formatting correctness
- successful build
- test execution

However:

- CI validates only implemented behavior
- it does not validate full system coverage
- authentication is tested but not system-wide

This means CI provides **confidence in the implemented slice**, but not complete system confidence yet.

---

## Existing CI Evidence

https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/actions/runs/23141529220

---

## Week 11 Evidence

**PR Link:**  
(PR LINK WILL BE INSERTED ONCE CREATED)

**Passing CI Run:**  
(PR LINK WILL BE INSERTED ONCE CREATED)