# Bug Triage + Regression Protection

## Issue 1
**Title:** Invalid score error message is unclear  
**Severity:** Major  

**Repro Steps:**
1. Start the server locally
2. Create a student
3. Submit an assessment with an invalid score such as `-5` or `150`
4. Observe the API response

**Expected Behavior:**  
The API should return a clear validation message explaining that the score must be within the accepted range.

**Actual Behavior:**  
The response is too vague or not specific enough to explain the failure clearly.

**Status:** Fixed  
**Evidence:** (PROJECT LINK PENDING)

---

## Issue 2
**Title:** Unknown student ID does not return a sufficiently clear error  
**Severity:** Major  

**Repro Steps:**
1. Start the server locally
2. Request an assessment submission or recommendation lookup using a fake student ID
3. Observe the API response

**Expected Behavior:**  
The API should clearly state that the student was not found for the provided `studentId`.

**Actual Behavior:**  
The response does not provide enough detail to quickly diagnose the problem.

**Status:** Fixed  
**Evidence:** (PROJECT LINK PENDING)

---

## Issue 3
**Title:** No request logging for health endpoint  
**Severity:** Minor  

**Repro Steps:**
1. Start the server locally
2. Call `GET /api/health`
3. Check the server output

**Expected Behavior:**  
A log entry should confirm that the request was received and handled successfully.

**Actual Behavior:**  
No useful diagnostic output is produced for the request.

**Status:** Fixed  
**Evidence:** (PROJECT LINK PENDING)

---

## Issue 4
**Title:** No request logging for student creation  
**Severity:** Minor  

**Repro Steps:**
1. Start the server locally
2. Call `POST /api/students`
3. Check the server output

**Expected Behavior:**  
A log entry should identify the endpoint and indicate that the request completed.

**Actual Behavior:**  
No useful request log is available.

**Status:** Open  
**Evidence:** (PROJECT LINK PENDING_IF FIXED)

---

## Issue 5
**Title:** Assessment submission failures are hard to trace  
**Severity:** Critical  

**Repro Steps:**
1. Start the server locally
2. Submit an invalid assessment request
3. Observe the response and server output

**Expected Behavior:**  
The response and log output should make it easy to understand what failed and where it failed.

**Actual Behavior:**  
The failure is not logged with enough detail to trace the issue efficiently.

**Status:** Open  
**Evidence:** (PROJECT LINK PENDING_IF FIXED)

---

## Issue 6
**Title:** Recommendation lookup failure lacks diagnostic context  
**Severity:** Major  

**Repro Steps:**
1. Start the server locally
2. Request the latest recommendation for an invalid or missing student record
3. Observe the response and server output

**Expected Behavior:**  
The system should return a clear error response and log enough context to troubleshoot the issue.

**Actual Behavior:**  
The result does not provide enough diagnostic information.

**Status:** Open  
**Evidence:** (PROJECT LINK PENDING_IF FIXED)

---

## Regression Protection Summary
The Week 9 fixes should include regression tests for the two most important corrected issues:
- invalid score validation
- invalid or unknown student ID handling

These tests should run in CI so the same bugs do not silently return in later changes.