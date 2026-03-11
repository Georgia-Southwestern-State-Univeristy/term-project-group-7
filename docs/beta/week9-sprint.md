# Week 9 Sprint Goal + Committed Backlog

## Sprint Goal
By Friday, users can complete the Beta MVP workflow more reliably through structured request logging, clearer error messages, and regression protection for common failures.

## Committed Backlog Items (Ranked)

### 1. Add structured logs for key API actions
**Owner:** Grey

**Acceptance Criteria:**
- `GET /api/health` writes a structured log entry
- `POST /api/students` writes a structured log entry
- `POST /api/students/{studentId}/assessments` writes a structured log entry
- `GET /api/students/{studentId}/recommendations/latest` writes a structured log entry

### 2. Improve error messages for common API failures
**Owner:** Grey

**Acceptance Criteria:**
- Invalid score returns a clear validation message
- Missing required fields return a clear validation message
- Unknown `studentId` returns a clear not-found message

### 3. Add structured error logs with useful context
**Owner:** Grey

**Acceptance Criteria:**
- Validation failures are logged with endpoint and reason
- Student lookup failures are logged with endpoint, `studentId`, and reason
- Error logs are distinct from successful request logs

### 4. Add regression tests for fixed Beta bugs
**Owner:** Grey

**Acceptance Criteria:**
- At least 2 fixed bugs have automated regression tests
- Regression tests run in CI
- The tests would fail if the bug returned

### 5. Document sprint evidence and shipped work
**Owner:** Grey

**Acceptance Criteria:**
- `docs/beta/week9-pr-index.md` is complete
- `docs/beta/bug-triage.md` is complete
- `docs/beta/observability.md` is complete
- Project Board sprint link is added before submission

## Evidence
**Project Board Sprint View:** https://github.com/orgs/Georgia-Southwestern-State-Univeristy/projects