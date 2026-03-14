# Week 10 Validation + Security Notes

## Risk 1: Teacher override endpoint could be called without access control
**Why this is specific to our system:**  
The MVP includes a teacher override route that changes recommendation behavior. Without server-side access control, any caller could attempt to use it.

**Before:**  
The endpoint accepted requests without checking auth or role.

**After:**  
The endpoint now requires a valid auth token and an approved role (`teacher` or `admin`).

**Mitigation Status:** Fixed

---

## Risk 2: Teacher override inputs were too weakly validated
**Why this is specific to our system:**  
The teacher override route accepts `activityId` and `reason`. Weak validation could allow invalid override decisions or poor operator feedback.

**Before:**  
Only missing fields were checked.

**After:**  
The endpoint now rejects:
- missing `activityId`
- missing `reason`
- too-short `reason`
- invalid `activityId` format

**Mitigation Status:** Fixed

---

## Risk 3: Error handling could confuse Beta users
**Why this is specific to our system:**  
Beta users need clear feedback when requests fail, especially around auth and validation.

**Before:**  
Failures were generic and did not clearly distinguish unauthorized, forbidden, or validation errors.

**After:**  
The API now returns clearer status codes and clearer JSON error messages:
- `401` for missing/invalid token
- `403` for wrong role
- `400` for validation failures

**Mitigation Status:** Fixed

## Validation Improvements Added
Validation was improved on these inputs:
1. `reason` in teacher override
2. `activityId` in teacher override

## Evidence
- PR link: (will be added after creation)
- Before/after behavior documented above