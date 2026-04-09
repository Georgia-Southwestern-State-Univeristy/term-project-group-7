# Bug Triage + Regression Protection

## Issue 1
**Title:** Invalid score error message was unclear  
**Severity:** Major  
**Repro Steps:**
1. Start the server
2. Create a student
3. Submit an assessment with score `101`
4. Observe the response

**Expected Behavior:**  
The API should clearly state that score must be within the accepted range.

**Actual Behavior:**  
The failure message was not documented as part of Beta bug evidence and needed regression protection.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/1 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/2

---

## Issue 2
**Title:** Unknown `studentId` failure lacked clear context  
**Severity:** Major  
**Repro Steps:**
1. Start the server
2. Request latest recommendation for a fake `studentId`
3. Observe the response

**Expected Behavior:**  
The API should clearly report that the student was not found.

**Actual Behavior:**  
The failure case needed clearer messaging and regression protection.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/2 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/3

---

## Issue 3
**Title:** No structured log for health endpoint  
**Severity:** Minor  
**Repro Steps:**
1. Start the server
2. Call `GET /api/health`
3. Check terminal output

**Expected Behavior:**  
A structured success log should be written.

**Actual Behavior:**  
No useful request log was produced.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/3 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/1

---

## Issue 4
**Title:** Student creation requests were not logged  
**Severity:** Minor  
**Repro Steps:**
1. Start the server
2. Call `POST /api/students`
3. Check terminal output

**Expected Behavior:**  
A structured success log should include endpoint, action, status, and `studentId`.

**Actual Behavior:**  
No useful request log was produced.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/4 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/1

---

## Issue 5
**Title:** Assessment submission failures were hard to trace  
**Severity:** Critical  
**Repro Steps:**
1. Start the server
2. Submit an invalid assessment request
3. Check response and logs

**Expected Behavior:**  
The response and error log should show what failed and why.

**Actual Behavior:**  
The failure was not logged with enough context.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/5 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/2

---

## Issue 6
**Title:** Recommendation lookup failure lacked diagnostic context  
**Severity:** Major  
**Repro Steps:**
1. Start the server
2. Request latest recommendation for an invalid student
3. Check response and logs

**Expected Behavior:**  
The API and logs should clearly show that the student was not found.

**Actual Behavior:**  
The failure lacked enough diagnostic context.

**Status:** Fixed  
**Evidence:** https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/issues/6 and https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/2

---

## Regression Protection Summary
The following fixed bugs now have regression tests:
- invalid score validation failure
- unknown student ID lookup failure

These tests run in CI and reduce the chance of the same failures returning later.