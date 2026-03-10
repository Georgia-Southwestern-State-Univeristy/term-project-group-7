# Week 9 Sprint Goal + Committed Backlog

## Sprint Goal
By Friday, users can complete the MVP workflow more reliably with clearer errors, better diagnostics, and regression protection.

## Committed Backlog Items

### 1. Add request logging for key API actions
**Owner:** Grey

**Acceptance Criteria:**
- Log entries are written for `GET /api/health`
- Log entries are written for `POST /api/students`
- Log entries are written for `POST /api/students/{studentId}/assessments`
- Log entries are written for `GET /api/students/{studentId}/recommendations/latest`

### 2. Add structured error logs for common failures
**Owner:** Grey

**Acceptance Criteria:**
- Validation failures are logged with endpoint context
- Student lookup failures are logged with endpoint context
- Error logs include enough detail to understand what failed

### 3. Improve invalid input error messages
**Owner:** Grey

**Acceptance Criteria:**
- Invalid score returns a clear error message
- Invalid or unknown student ID returns a clear error message
- API responses explain what failed in a way that is easy to debug

### 4. Add regression tests for fixed bugs
**Owner:** Grey

**Acceptance Criteria:**
- At least 2 fixed bugs have matching automated tests
- Tests run successfully in CI
- The tests would fail again if the bug returned

### 5. Document sprint evidence, bug triage, and observability
**Owner:** Grey

**Acceptance Criteria:**
- `docs/beta/week9-pr-index.md` exists
- `docs/beta/bug-triage.md` exists
- `docs/beta/observability.md` exists
- Evidence links are added before submission

## Evidence
Project Board Sprint View: (PROJECT LINK PENDING)