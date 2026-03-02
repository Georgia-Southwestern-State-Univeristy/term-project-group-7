# Demo Readiness (Week 7)

## Goal (5–7 minutes)

Demonstrate the MVP demo path end-to-end:

1. Health check
2. Create student
3. Add assessment
4. Retrieve latest recommendation
5. (Optional) Teacher override

This demo proves:
- The server runs locally
- Core MVP endpoints function
- Rule-based recommendation logic works
- Behavior is protected by automated tests
- The system is repeatable without external dependencies

---

## Prerequisites

- Windows 10/11
- Visual Studio 2026 (Community) with C++ tools
- CMake installed
- Git installed

Server runs locally at:
http://127.0.0.1:5000

The application uses in-memory storage. No database required.

---

## Build + Run (Exact Commands)

From repository root:

1.
cmake -S . -B build

2.
cmake --build build --config Debug

3. Run the server:
build\Debug\server.exe

4. Verify:
curl http://127.0.0.1:5000/api/health

Expected response:
{"status":"ok","service":"cpp"}

---

## Seed Data Plan (Consistent Demo Data)

Use the same demo data every time:

- Student name: David
- gradeLevel: 7
- skill: fractions
- score: 62

Reason:
Score 62 reliably triggers the “fractions_foundations” rule recommendation.

If demo data becomes inconsistent, restart the server to reset in-memory storage.

---

# Step-by-Step Demo Script (Copy/Paste Commands)

## 1) Health Check

curl http://127.0.0.1:5000/api/health

Expect:
200 + {"status":"ok","service":"cpp"}

---

## 2) Create Student

curl -X POST http://127.0.0.1:5000/api/students ^
 -H "Content-Type: application/json" ^
 -d "{\"name\":\"David\",\"gradeLevel\":7}"

Expect:
201 + {"studentId":"<generated-id>"}

Copy the returned studentId.

---

## 3) Add Assessment

Replace <studentId> with the actual ID:

curl -X POST http://127.0.0.1:5000/api/students/<studentId>/assessments ^
 -H "Content-Type: application/json" ^
 -d "{\"skill\":\"fractions\",\"score\":62}"

Expect:
201

---

## 4) Get Latest Recommendation

curl http://127.0.0.1:5000/api/students/<studentId>/recommendations/latest

Expect:
200 + 
{
  "activityId": "fractions_foundations",
  "source": "rules"
}

This confirms the rule engine is functioning.

---

## 5) Optional: Teacher Override

curl -X POST http://127.0.0.1:5000/api/students/<studentId>/teacher-override ^
 -H "Content-Type: application/json" ^
 -d "{\"activityId\":\"fractions_practice_set_A\",\"reason\":\"Teacher override for extra support\"}"

Expect:
200 + 
{
  "activityId": "fractions_practice_set_A",
  "source": "override"
}

Calling the recommendation endpoint again should now return the override result.

---

# Known Issues and Handling

If port 5000 is already in use:
- Stop the running server
- Restart terminal
- Run build\Debug\server.exe again

If build fails:
- Delete build folder
- Re-run:
  cmake -S . -B build
  cmake --build build --config Debug

If demo data behaves unexpectedly:
- Stop the server
- Restart build\Debug\server.exe to reset in-memory storage

---

# Fallback Plan

If the demo machine fails:

1. Teammate clones repository
2. Runs:
   cmake -S . -B build
   cmake --build build --config Debug
3. Runs:
   build\Debug\server.exe
4. Uses the exact curl commands above

No external services required.

---

# Test Protection

The demo path is protected by automated tests that run in CI:

- Health endpoint test
- MVP service logic test
- Validation tests
- Boundary tests

CI pipeline executes tests automatically on every PR merge.