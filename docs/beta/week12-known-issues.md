# Week 12 Known Issues

## Issue 1: CLI does not exit cleanly
- **Description:** Selecting option `0` does not terminate the program at times.
- **Impact:** User must manually terminate using `Ctrl + C`.
- **Severity:** Medium
- **Likely Cause / Affected Area:** CLI menu loop control in main execution flow
- **Workaround:** Use `Ctrl + C`
- **Planned Fix:** Implement proper loop termination logic

---

## Issue 2: No persistent storage
- **Description:** User progress and results are not saved.
- **Impact:** Data is lost after program exit.
- **Severity:** Medium
- **Likely Cause / Affected Area:** No file or database persistence layer implemented
- **Planned Fix:** Add file-based or database persistence

---

## Issue 3: Limited authentication
- **Description:** No login or user tracking exists.
- **Impact:** No personalization or user-specific workflows.
- **Severity:** High
- **Likely Cause / Affected Area:** Authentication module not implemented
- **Planned Fix:** Add basic authentication system and role handling

---

## Issue 4: No browser interface
- **Description:** System only runs via CLI.
- **Impact:** Limits usability and demonstration scope.
- **Severity:** Low
- **Likely Cause / Affected Area:** No frontend or web server implementation
- **Planned Fix:** Consider adding a web-based interface in future versions

---

## Issue 5: Limited test coverage for edge cases
- **Description:** Some edge cases (large numbers, decimal precision, repeated invalid input) are not fully tested.
- **Impact:** Potential incorrect behavior under uncommon inputs.
- **Severity:** Medium
- **Likely Cause / Affected Area:** Problem generation and input validation logic
- **Planned Fix:** Expand unit tests to cover edge cases and boundary conditions