# Week 13 Observability + Support Visibility

## Goal
Make the system easier to monitor, debug, and support by improving visibility into request handling, failure conditions, and support-facing behavior.

## Improvement 1: Clearer validation failure visibility
### What issue or blind spot it addresses
Before this improvement, validation failures could be understood only by reading scattered service logic. That made support and debugging slower.

### Where in the system it applies
`src/mvp_service.h`

### What changed
Validation behavior for student creation, assessment submission, and teacher override flow is now centralized into helper methods:
- `validate_student_input(...)`
- `validate_assessment_input(...)`
- `validate_teacher_override_input(...)`

### How it helps a future maintainer or operator
A maintainer can now trace validation behavior in one place and quickly understand why requests are being rejected.

### Before
Validation checks were repeated across multiple service methods.

### After
Validation behavior is centralized and easier to inspect, debug, and change safely.

## Improvement 2: Clearer missing-student failure behavior
### What issue or blind spot it addresses
Student lookup failures were repeated in multiple methods, which increased the chance of inconsistent error behavior.

### Where in the system it applies
`src/mvp_service.h`

### What changed
Student existence checking was moved into a shared helper method:
- `require_student(...)`

### How it helps a future maintainer or operator
A maintainer can see that missing-student failures are handled consistently in one place instead of having to inspect multiple methods.

### Before
Student lookup and failure handling were duplicated.

### After
Missing-student behavior is centralized and easier to follow.

## Improvement 3: Better support visibility through stronger automated protection
### What issue or blind spot it addresses
Weak or placeholder tests do not help future maintainers detect whether refactoring broke support-critical validation behavior.

### Where in the system it applies
`tests/test_validation_teacher_override_missing_reason.cpp`  
`tests/test_refactor_assessment_missing_skill.cpp`

### What changed
The week 13 work replaced weak validation coverage with service-level test coverage and added a new refactor-protection test for missing assessment skill input.

### How it helps a future maintainer or operator
A future maintainer can make code-health improvements with more confidence because the tests now protect important validation behavior.

### Before
One validation-related test did not meaningfully exercise the service.

### After
The service validation behavior is directly tested and protected.

## Evidence
- Observability PR: [PR LINK]
- Supporting PR or same PR: [PR LINK]