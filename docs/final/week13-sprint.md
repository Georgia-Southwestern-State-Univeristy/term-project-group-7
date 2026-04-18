# Week 13 Sprint Goal + Quality-Focused Backlog

## Sprint Goal
Improve maintainability, reliability, and support readiness by reducing code duplication, strengthening diagnostics, and adding regression protection around core student learning flows.

## Evidence
- Sprint evidence was tracked directly in the Week 13 submission PR and supporting docs: https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/43

## Committed Backlog Items

### 1. Refactor recommendation and validation flow
- **Owner:** Grey
- **Acceptance Criteria:**
  - Recommendation decision rules are moved into a clearer shared service or helper structure.
  - Validation logic is not duplicated across multiple routes.
  - Existing behavior remains unchanged for valid and invalid score cases.

### 2. Improve structured logging for support visibility
- **Owner:** Grey, Hugee, James
- **Acceptance Criteria:**
  - Requests log endpoint, action, and result status.
  - Failures log enough context to diagnose the problem.
  - Logs distinguish success cases from validation or lookup failures.

### 3. Add startup/config validation
- **Owner:** Hugee, Jimoh
- **Acceptance Criteria:**
  - Server validates required startup assumptions before serving traffic.
  - Failure states are surfaced clearly in terminal output.
  - Invalid startup conditions do not fail silently.

### 4. Strengthen frontend/server fallback behavior
- **Owner:** Ridhwaan
- **Acceptance Criteria:**
  - Unsupported or missing routes return clearer responses.
  - User-facing error states are more explicit.
  - Basic fallback behavior is documented for maintainers.

### 5. Add regression tests for recent weak spots
- **Owner:** Grey
- **Acceptance Criteria:**
  - At least 2 regression tests cover recent bugs or fragile behavior.
  - At least 1 test covers refactored code.
  - At least 1 test covers reliability, error handling, or observability behavior.

### 6. Update architecture and hand-off documentation
- **Owner:** Team
- **Acceptance Criteria:**
  - Architecture snapshot matches the real current system.
  - Hand-off draft explains setup, stack, weaknesses, and next steps.
  - Week 13 evidence links are included before submission.