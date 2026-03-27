# Week 11 Sprint Goal + Integration Backlog

## Sprint Goal
By the end of Week 11, the team will prove one meaningful end-to-end workflow through the actual system—student creation through assessment submission to recommendation retrieval—while tightening failure handling, documenting known instability honestly, and protecting the workflow with automated tests and CI evidence.

## Committed Backlog Items

### 1. Prove the primary end-to-end workflow through the running system
**Owner:** Grey

**Acceptance Criteria:**
- The workflow starts with student creation and ends with retrieval of the latest recommendation
- The workflow uses the actual implemented API endpoints, not only documentation
- Evidence includes run notes and links to implementation PRs

---

### 2. Strengthen workflow reliability for common failure cases
**Owner:** Grey

**Acceptance Criteria:**
- Invalid assessment score is rejected with a clear error
- Recommendation lookup for an unknown student returns a safe failure response
- Request-body and required-field failures are documented with before/after behavior

---

### 3. Capture reliability risks that are specific to this system
**Owner:** Grey

**Acceptance Criteria:**
- At least 3 concrete system-specific reliability or failure risks are identified
- At least 2 already-implemented reliability improvements are documented
- Remaining risks deferred to Week 12+ are listed honestly

---

### 4. Protect the primary workflow with automated tests
**Owner:** Grey

**Acceptance Criteria:**
- At least 4 automated tests tied to workflow behavior are identified and documented
- At least 2 tests directly cover the assessment-to-recommendation path
- At least 1 failure-path or regression test is included

---

### 5. Capture CI stability evidence for the current codebase
**Owner:** Grey

**Acceptance Criteria:**
- The CI pipeline stages are documented
- A passing GitHub Actions run is linked
- Any mismatch between documentation and implementation is called out honestly

---

### 6. Publish Week 11 Beta readiness status
**Owner:** Grey

**Acceptance Criteria:**
- What works now is summarized in 3–5 bullets
- Known issues are ranked high / medium / low
- The readiness judgment states clearly whether the team is on track for Week 12 Beta

## Why this backlog fits Week 11
More than half of this week’s backlog is directly tied to integration, workflow completion, reliability, failure handling, and testing:

- Item 1: integration + workflow completion
- Item 2: reliability + failure handling
- Item 3: reliability
- Item 4: testing
- Item 5: CI stability

## Evidence

**Project Board Sprint View:**  
https://github.com/orgs/Georgia-Southwestern-State-Univeristy/projects

**Existing implementation/testing evidence already present in the repository:**
- Week 10 auth / validation / regression tests PR:  
  https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/37
- Week 10 access control + validation documentation/implementation PR:  
  https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/38
- Prior sprint evidence doc:  
  `docs/beta/week10-sprint.md`

**Week 11 submission PR:**  
Week 11 submission PR:
https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/40