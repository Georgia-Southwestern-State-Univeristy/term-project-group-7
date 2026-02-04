# Risks and Trade-Offs (Team)

## Trade-Offs
- **Rules-based logic vs ML personalization:** explainable and implementable now, but less adaptive long-term.
- **Local prototype vs scalable deployment:** minimal infrastructure now; scaling needs DB + hosting changes.
- **Transparency vs sophistication:** decisions are understandable, but may not optimize learning outcomes as well as ML.

## Key Risks and Mitigations
- **Risk: Rule thresholds produce weak recommendations**
  - Mitigation: calibrate using sample student profiles; allow teacher override; log decision rationale.
- **Risk: Data quality issues (missing assessments, inconsistent scoring)**
  - Mitigation: input validation; default handling; clear error feedback.
- **Risk: Privacy and student data exposure**
  - Mitigation: minimize stored PII; role-based access; local-only storage for prototype.
- **Risk: SQLite / local DB limits**
  - Mitigation: document migration plan to hosted DB; isolate persistence behind interfaces.
