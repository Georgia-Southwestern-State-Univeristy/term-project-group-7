# Observability Starter + Error Handling

## Where Logs Live
Logs are written to the terminal where the C++ server is running:

- structured request and action logs go to standard output
- structured error logs go to standard error

Each log line is a single JSON object (JSONL) for easy filtering and parsing.

## How to View Logs

1. Build and run the server locally
2. Send requests to the API endpoints
3. Observe JSON log lines in the same terminal session

## What Events Are Logged

Requests:
- `http_request` for every handled request (method, path, status, request_id)

User actions (structured):
- `create_student`
- `add_assessment`
- `get_latest_recommendation`
- `teacher_override`

Errors (structured):
- `validation_error` for missing/invalid inputs
- `domain_error` for business-rule failures (e.g., unknown student)
- `http_error` for low-level HTTP parsing/transport errors

Every entry includes `ts`, `level`, `event`, and (when available) `request_id`.

## Logged Failure Cases

Two common failures that are validated and logged with clear messages:

- missing required fields (e.g., `name` + `gradeLevel`, `skill` + `score`)
- empty request body on POST endpoints

Additional domain validations (also logged):
- invalid grade level (must be 6..8)
- invalid score (must be 0..100)
- unknown `studentId`

## Correlating User Actions to Logs

Each API response includes `X-Request-Id`. The same value appears in log lines as `request_id`.

Example flow:
API request -> server generates `X-Request-Id` -> log line written

Example log lines:
```json
{"ts":"2026-03-14T19:32:18Z","level":"info","event":"http_request","request_id":"req-1710448338123-0","method":"POST","path":"/api/students","status":201}
{"ts":"2026-03-14T19:32:18Z","level":"info","event":"create_student","request_id":"req-1710448338123-0","studentId":"student_1","name":"Sam","gradeLevel":7}
```

To trace a user action, find the `X-Request-Id` from the API response and search for the same `request_id` in the logs.