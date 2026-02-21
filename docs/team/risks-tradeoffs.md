# Risks and Trade-Offs (Team)

## Trade-Offs
- **Rules-based logic vs ML personalization:** Explainable and implementable now, but less adaptive in the long term.
- **Local prototype vs scalable deployment:** Minimal infrastructure initially; scaling requires database and hosting changes.
- **Transparency vs sophistication:** Decisions are understandable but may not optimize learning outcomes as well as ML approaches.

## Key Risks and Mitigations
- **Risk: Rule thresholds produce weak recommendations**  
  Calibrate rules using sample student profiles; allow teacher override; log decision rationale.

- **Risk: Data quality issues (missing assessments, inconsistent scoring)**  
  Input validation, default handling, and clear error feedback.

- **Risk: Privacy and student data exposure**  
  Minimize stored PII, enforce role-based access control, and use local-only storage for the prototype.

- **Risk: Role-based access control bugs expose teacher or administrator views to students**  
  Enforce server-side role checks in addition to UI controls and add tests for role-gated routes.

- **Risk: SQLite / local database limits**  
  Document a migration plan to a hosted database and isolate persistence behind well-defined interfaces.

- **Risk: Poor content tagging or mapping reduces recommendation effectiveness**  
  Require explicit grade, topic, and skill tags for all content and allow teacher feedback or overrides.


- **Risk: Contract and code drift (OpenAPI says one thing, server does another).**  
  Treat `docs/api/openapi.yaml` as the source of truth; update contract + implementation in the same PR.

- **Risk: CI signal too weak (build passes while behavior breaks).**  
  Add at least one automated test validating MVP behavior and run it in CI using `ctest`.

- **Risk: Demo not repeatable on teammate machines.**  
  README must include exact build/run commands and exact curl requests (Hello Path).