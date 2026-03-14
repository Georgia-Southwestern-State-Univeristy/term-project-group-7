# Week 10 UX Improvements

## UX Improvement 1: Clearer auth failure responses
**Before:**  
Protected teacher actions could fail without clearly telling the user whether the problem was missing auth or insufficient role.

**After:**  
The API now clearly separates:
- `401 Unauthorized`
- `403 Forbidden`

**User Benefit:**  
Users and testers can understand whether they need credentials or different permissions.

---

## UX Improvement 2: Clearer validation messages for teacher override
**Before:**  
Teacher override failures were less specific and did not fully explain what input needed to be fixed.

**After:**  
The API now returns clear messages for:
- missing `activityId`
- missing `reason`
- too-short `reason`
- invalid `activityId` format

**User Benefit:**  
Less trial-and-error when correcting requests during Beta testing.

## Evidence
- CI link: (will be added after creation)
- PR link: (will be added after creation)
- Before/after behavior documented above