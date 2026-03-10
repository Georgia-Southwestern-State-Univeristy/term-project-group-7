# Observability Starter + Error Handling

## Where Logs Live
Logs are currently written to the server console output while the application is running locally. Informational request logs should appear on standard output, and error logs should appear on standard error.

## How to View Logs
Run the server locally from the terminal using the project README instructions. While the server is running, make requests to the API endpoints and observe the log output in the same terminal session.

## What Events Are Logged
The application should log the following events:
- health endpoint requests
- student creation requests
- assessment submission requests
- latest recommendation requests
- validation failures
- student lookup failures

## How to Correlate a User Action to a Log Entry
Each log entry should include the endpoint and action context. When available, the log should also include the `studentId` so a request can be connected to a specific learner action. This makes it easier to trace a request from the API call to the resulting response or failure.

## Sample Log Snippet
```text
[INFO] endpoint=/api/health status=200 action=health_check
[INFO] endpoint=/api/students status=201 action=create_student studentId=student-1
[INFO] endpoint=/api/students/{studentId}/assessments status=201 action=submit_assessment studentId=student-1
[ERROR] endpoint=/api/students/{studentId}/assessments status=400 action=submit_assessment reason=invalid_score
[ERROR] endpoint=/api/students/{studentId}/recommendations/latest status=404 action=get_latest_recommendation reason=student_not_found