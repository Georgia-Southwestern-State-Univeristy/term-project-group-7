# Week 10 Sprint Goal + Committed Backlog

## Sprint Goal
By Friday, the Beta MVP is safer and easier to use through basic server-side access control, stronger input validation, and tests that prove the new protections work.

## Committed Backlog Items (Ranked)

### 1. Protect teacher override with server-side access control
**Owner:** Grey

**Acceptance Criteria:**
- Unauthorized requests to `POST /api/students/{studentId}/teacher-override` return `401`
- Requests with the wrong role return `403`
- Authorized teacher/admin requests succeed

---

### 2. Document authentication and protected routes
**Owner:** Grey

**Acceptance Criteria:**
- `docs/security/auth.md` explains how auth works
- Protected endpoint(s), role model, and limitations are documented
- Evidence section includes PR link and demo notes

---

### 3. Strengthen validation on teacher override
**Owner:** Grey

**Acceptance Criteria:**
- Missing `activityId` returns clear `400` error
- Missing or too-short `reason` returns clear `400` error
- Invalid `activityId` format returns clear `400` error

---

### 4. Document Week 10 security risks and fixes
**Owner:** Grey

**Acceptance Criteria:**
- `docs/security/week10-security-notes.md` lists 3 concrete risks from this system
- At least 2 mitigations are implemented and described
- Before/after behavior is documented

---

### 5. Add Week 10 auth/validation/regression tests
**Owner:** Grey

**Acceptance Criteria:**
- At least 4 new tests are added
- At least 2 tests cover authorized vs unauthorized behavior
- At least 1 validation failure test is added
- At least 1 regression test is added

---

### 6. Improve Beta usability for common failure cases
**Owner:** Grey

**Acceptance Criteria:**
- At least 2 UX improvements are implemented
- `docs/security/week10-ux.md` explains before/after behavior
- Evidence section includes PR link and CI note

---

## Evidence

**Project Board Sprint View:**
https://github.com/orgs/Georgia-Southwestern-State-Univeristy/projects

**PRs Implementing Sprint Work:**

Auth + documentation PR  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/36

Access control + validation implementation PR  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/38

Auth / validation / regression tests PR  
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/37