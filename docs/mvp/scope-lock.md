# MVP Scope Lock (Team)

**Rule:** If it’s not explicitly listed below, it does **not** consume sprint time this week.

## MVP User Stories (6)
1. **As a teacher, I want to create a student profile, so that I can track learning activity for a specific learner.**
2. **As a teacher, I want to submit a skill assessment score for a student, so that the system can generate a next-step recommendation.**
3. **As a teacher, I want to view the student’s latest recommendation, so that I can decide what the student should work on next.**
4. **As a teacher, I want to override the recommendation, so that I can apply professional judgment when needed.**
5. **As a user, I want a health endpoint, so that I can confirm the app is running end-to-end.**
6. **As a developer, I want an automated test that validates the recommendation behavior, so that CI can prevent regressions.**

## Explicit Non-Goals (Not in MVP)
- No real authentication/authorization (only a documented placeholder header).
- No database or persistence (in-memory only; data resets on restart).
- No student login UI, no accounts, no roles beyond teacher actions.
- No ML/AI personalization (rules-based recommendation only).
- No dashboards/analytics, reports, notifications, or email/SMS.
- No admin panel, no deployment to cloud required for MVP grading.

## Midterm Demo Script (Exact Path)
1. Start server locally.
2. Open `http://127.0.0.1:5000/` and show the “OK – App is running” page.
3. Call `GET /api/health` and show HTTP 200 response.
4. Call `POST /api/students` to create a student; copy returned `studentId`.
5. Call `POST /api/students/{studentId}/assessments` with a sample score.
6. Call `GET /api/students/{studentId}/recommendations/latest` and show the generated recommendation.
7. Call `POST /api/students/{studentId}/teacher-override` and set a manual activity.
8. Re-call `GET /api/students/{studentId}/recommendations/latest` and show `source=override`.

## Risks (Top 3) + Mitigations
1. **Risk: Contract drift (endpoint/payload mismatch across team).**  
   Mitigation: `docs/api/openapi.yaml` is the source of truth; changes require PR review.
2. **Risk: C++ JSON/HTTP plumbing slows integration.**  
   Mitigation: keep payloads minimal; one real path only; unit test targets service layer.
3. **Risk: PR becomes too large to review / integrate.**  
   Mitigation: merge early; keep changes limited to A/B docs + one integrated behavior + one test.
   