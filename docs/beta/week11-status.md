# Week 11 Known Issues + Beta Readiness Snapshot

---

## What Works Now

- The system runs end-to-end from student creation to recommendation retrieval
- Rules-based recommendation engine is functioning correctly
- Validation prevents invalid inputs and protects system behavior
- Automated tests cover workflow, boundaries, failures, and regressions
- CI pipeline builds, tests, and validates formatting successfully

---

## Known Issues

### High
- data is stored in-memory only (lost on restart)
- authentication is limited to a single endpoint (not system-wide)

### Medium
- JSON parsing is minimal and not robust
- only latest recommendation is stored (no history)
- documentation may slightly exceed implementation in auth scope

### Low
- UI proof is minimal
- system is intentionally narrow (thin vertical slice)

---

## Deferred Work

- persistent database storage
- full authentication system
- role-based access control
- expanded teacher dashboard
- full API contract validation
- deeper integration testing

---

## Project Evidence

Project Board:  
https://github.com/orgs/Georgia-Southwestern-State-Univeristy/projects

Supporting Docs:
- `docs/beta/week10-sprint.md`
- `docs/mvp/scope-lock.md`
- `docs/mvp/demo-readiness.md`

---

## Beta Readiness Judgment (CRITICAL SECTION)

The system has progressed from a simple working prototype into a functional thin vertical slice that demonstrates meaningful system behavior. The end-to-end workflow operates correctly, recommendations are generated based on defined rules, and failure cases are handled more safely than in earlier stages. Automated testing and CI provide a foundation for maintaining stability.

However, the system is not fully Beta-ready yet.

The most significant limitation is the authentication model. While it is correctly implemented and thoroughly tested for a specific endpoint, it is intentionally minimal and not applied across the system. This creates a gap between the demonstrated behavior and what would be expected in a realistic application.

Additionally, the system relies entirely on in-memory storage, meaning all data is lost on restart. This limits the system’s reliability and realism.

The team is on track for Week 12 Beta only if:
- authentication is expanded beyond a single endpoint
- persistence is introduced or addressed
- documentation and implementation are fully aligned

These limitations are clearly understood and documented, not hidden, and addressing them will determine whether the system meets the Beta standard.