# Week 7 Status (MVP Progress Evidence)

**Project Board (evidence):** <(https://github.com/orgs/Georgia-Southwestern-State-Univeristy/projects/24)>

> Rule: “Done” means the story is merged to `main` with CI checks passing.

## Story Status

| MVP Story | Status | Evidence (PR link / Notes) |
|---|---|---|
| User Story 7: Health endpoint | Done | PR: <https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/20> |
| User Story 6: Create student profile | Done | PR: <https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/20> |
| User Story 3: Immediate feedback + recommendation | Done | PR: <https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/20> |
| User Story 8: Automated tests for recommendation behavior | In Progress | PR: <https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7/pull/21> (open) |
| User Story 5: Teacher views performance | Blocked | Blocked: out of MVP scope / not implemented this sprint |

## Scope Changes
No scope changes this week. We are keeping the Week 6 scope lock to focus on delivering fewer stories end-to-end with CI coverage.

## Updated Demo Outline (what we can actually show right now)
- Build + run server locally
- `GET /api/health` returns 200
- `POST /api/students` returns 201 + studentId
- `POST /api/students/{studentId}/assessments` returns 201
- `GET /api/students/{studentId}/recommendations/latest` returns 200 + `source:"rules"`
- (Optional) `POST /api/students/{studentId}/teacher-override` then latest recommendation returns `source:"override"`

# User Stories

**User Story 1:** As a student, I want to solve math problems, so that I can perform better in my math class.

**User Story 2:** As a student I want to work on specific math topics, so that I can improve the areas that I'm underperforming in.

**User Story 3:** As a student I want to receive immediate feedback on my performance, so that I can know if I have a correct understanding of the topic.

**User Story 4:** As a student I want an explanation of the questions that I got wrong, so that I can improve my knowledge on the topics.

**User Story 5:** As a teacher I want to view my student's performance, so that I can provide additional resources to their weaknesses.

**User Story 6:** As a teacher, I want to create a student profile, so that I can track learning activity for a specific learner.

**User Story 7:** As a user, I want a health endpoint, so that I can confirm the app is running end-to-end.

**User Story 8:** As a developer, I want an automated test that validates the recommendation behavior, so that CI can prevent regressions.


# Non-Goals

**No full curriculum:** The MVP will be limited to basic mathematical operations (i.e. addition, subtraction, multiplication, and division). 

**No UI:** The MVP has no GUI/web frontend. All interaction is via HTTP endpoints (curl/browser).

**Advanced Analytics:** The MVP will use simple analysis to determine the student's performance (i.e. correct answers vs. incorrect answers, scores on individual topics, and cumulative score). The MVP will not determine statistical trends or class averages.

**Authentication:** The MVP will not include full user authentication. User logins, user accounts, passwords, and security verification are out of scope.

**No database persistence:** The MVP uses in-memory storage only. Data resets when the server restarts.

**AI/ML:** The MVP will not use AI/ML for analytics or recommend a learning path.

**Reporting:** The MVP will not have a data analytics dashboard or generate student performance reports.

**Administrative Access:** The MVP will not not have any additional access or privileges associated with administrative access.

**Cloud/Web-based Deployment:** The MVP will operate locally and will not be operated in a web-based or cloud environment.


# Demo Script

**Introduction**
1. Navigate to the local project directory.
2. Build and run the server.
3. Confirm the server is running at `http://127.0.0.1:5000`.

**Step 1: Health check**
- Request: `GET /api/health`
- Proof: returns JSON with `"status":"ok"` and HTTP 200.

**Step 2: Create a student**
- Request: `POST /api/students`
- Body: `{ "name": "Alex", "gradeLevel": 7 }`
- Proof: returns a `studentId` and HTTP 201.

**Step 3: Add an assessment**
- Request: `POST /api/students/{studentId}/assessments`
- Body: `{ "skill": "fractions", "score": 62 }`
- Proof: returns an assessment object and HTTP 201.

**Step 4: View latest recommendation**
- Request: `GET /api/students/{studentId}/recommendations/latest`
- Proof: returns a recommendation with `source: "rules"` and HTTP 200.

**Step 5: Teacher override (optional but supported by contract)**
- Request: `POST /api/students/{studentId}/teacher-override`
- Body: `{ "activityId": "fractions_practice_set_A", "reason": "Teacher override for targeted practice." }`
- Proof: `GET /recommendations/latest` now returns `source: "override"`.