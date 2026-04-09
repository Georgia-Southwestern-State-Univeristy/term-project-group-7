# Week 11 Reliability + Failure Handling

## Goal
Strengthen system behavior when the primary workflow goes wrong and document concrete, implementation-specific reliability behavior tied to the actual code.

---

## Reliability Risk 1: Invalid assessment score can break recommendation logic

### Why this is specific to our system
The recommendation engine directly depends on assessment score input. Invalid scores would produce incorrect recommendations or inconsistent system behavior.

### Before
Invalid scores were identified as a failure case that needed validation and regression protection.

### After
The system now safely rejects invalid scores:

- valid range enforced: `0..100`
- invalid values do not create an assessment
- invalid values do not generate recommendations
- error response clearly communicates the issue

### Evidence
- Implementation: `src/mvp_service.h`
- Test: `tests/test_failure_invalid_score.cpp`
- Prior bug documentation: `docs/beta/bug-triage.md`

---

## Reliability Risk 2: Recommendation lookup for unknown student causes unclear failure

### Why this is specific to our system
Recommendation retrieval is part of the main workflow. If the system cannot distinguish a missing student from a system error, debugging and user understanding break down.

### Before
Unknown-student lookups were identified as a regression risk.

### After
The system now handles this safely:

- returns `student not found`
- does not return invalid or fake data
- logs the failure with request context
- response is consistent and safe

### Evidence
- Implementation: `src/mvp_service.h`
- Route handling: `src/server.cpp`
- Test: `tests/test_regression_unknown_student_recommendation.cpp`

---

## Reliability Risk 3: Missing request body or required fields breaks workflow early

### Why this is specific to our system
The workflow relies on structured JSON input. Missing data must fail early and clearly.

### Before
Missing-field cases were potential failure points.

### After
The server validates requests before processing:

For `POST /api/students`:
- empty body → `400` ("request body is required")
- missing fields → `400` ("name and gradeLevel are required")

For `POST /api/students/{studentId}/assessments`:
- empty body → `400`
- missing fields → `400` ("skill and score are required")

### Evidence
- Implementation: `src/server.cpp`
- Logging reference: `docs/beta/observability.md`

---

## Reliability Risk 4: Authentication is limited to a thin slice (NEW — FROM FEEDBACK)

### Why this matters
Authentication currently exists only for a single endpoint and uses a static token model.

### Current Behavior
- only teacher override endpoint is protected
- static token-based validation
- no system-wide enforcement

### Why this is a risk
- most endpoints are not protected
- behavior is not representative of real-world systems
- creates mismatch between expected system security and actual implementation

### What is working correctly
- authorized / unauthorized / forbidden behavior is implemented correctly
- validation logic is enforced
- test coverage exists for all auth scenarios

### Evidence
- `tests/test_auth_teacher_override_authorized.cpp`
- `tests/test_auth_teacher_override_unauthorized.cpp`
- `tests/test_validation_teacher_override_missing_reason.cpp`

### Why this is deferred
Expanding authentication to:
- all endpoints
- role-based access control
- session/login flow

is intentionally deferred to Week 12+ to maintain focus on the thin vertical slice.

---

## User-Facing Error Improvements

The system now provides clear messages instead of silent failures:

- missing request → "request body is required"
- missing fields → specific required field message
- invalid score → "score must be 0..100"
- unknown student → "student not found"

These improvements make failures actionable and understandable.

---

## Remaining Risks Deferred to Week 12+

- no persistent storage (data lost on restart)
- authentication not system-wide
- minimal JSON parsing approach
- no recommendation history tracking

---

## Reliability Judgment

The system now handles multiple real failure scenarios safely and predictably. Core workflow reliability has improved significantly through validation, error handling, and regression testing.

However, the system is not fully production-ready. The most important remaining risks are limited authentication coverage and lack of persistence. These are known, documented, and intentionally deferred, not ignored.