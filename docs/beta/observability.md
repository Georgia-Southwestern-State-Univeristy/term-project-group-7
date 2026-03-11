# Observability Starter + Error Handling

## Where Logs Live
Logs are written to the terminal where the C++ server is running:
- successful request logs go to standard output
- error logs go to standard error

## How to View Logs
1. Build and run the server locally
2. Send requests to the API endpoints
3. Observe log output in the same terminal session

## What Events Are Logged
The Beta starter logs the following:
- `GET /api/health`
- `POST /api/students`
- `POST /api/students/{studentId}/assessments`
- `GET /api/students/{studentId}/recommendations/latest`

It also logs common failure cases:
- missing required fields
- invalid score validation failures
- unknown `studentId` lookup failures

## How to Correlate a User Action to a Log Entry
Each log entry includes:
- `requestId`
- endpoint
- action
- HTTP status
- relevant request context such as `studentId`, score, or failure reason

This allows a tester to match one API call to one log line and quickly identify what happened.

## Example Failure Cases With Clear Error Messages

### Case 1: Invalid score
The API returns a clear validation error when `score` is outside `0..100`.

### Case 2: Unknown student ID
The API returns a clear not-found error when the provided `studentId` does not exist.

## Sample Log Snippet
```text
[INFO] requestId=req-1 endpoint=/api/health status=200 action=health_check
[INFO] requestId=req-2 endpoint=/api/students status=201 action=create_student studentId=student_1 gradeLevel=7
[INFO] requestId=req-3 endpoint=/api/students/{studentId}/assessments status=201 action=submit_assessment studentId=student_1 skill=fractions score=62
[ERROR] requestId=req-4 endpoint=/api/students/{studentId}/assessments status=400 action=submit_assessment reason=validation_failed studentId=student_1 score=101
[ERROR] requestId=req-5 endpoint=/api/students/{studentId}/recommendations/latest status=404 action=get_latest_recommendation reason=student_not_found studentId=missing_student