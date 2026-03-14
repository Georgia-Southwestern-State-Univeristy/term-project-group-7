# Week 10 Authentication + Access Control

## Authentication Approach
The Beta MVP uses a minimal header-based token check for protected teacher actions.

Protected requests must include:
- `X-Auth-Token`
- `X-User-Role`

## Role Model
The system supports these roles:
- `teacher`
- `admin`
- `student`

For Week 10, the protected endpoint accepts:
- `teacher`
- `admin`

The `student` role is not allowed to perform teacher override actions.

## Protected Route
The following endpoint is protected:

- `POST /api/students/{studentId}/teacher-override`

## Access-Control Rule
Only `teacher` or `admin` users with the correct auth token may submit teacher overrides.

Unauthorized behavior:
- missing token → `401 Unauthorized`
- wrong token → `401 Unauthorized`
- wrong role → `403 Forbidden`

## Security Assumptions
This is a minimal Beta-ready access-control layer, not a full production identity system.

Assumptions:
- tokens are shared only with approved teacher/admin users
- the token is checked server-side
- role enforcement happens on the server, not only in the UI

## Limitations
Current limitations:
- static token instead of real session/OAuth login
- no token expiration
- no rate limiting
- no audit persistence beyond logs

## Demo Notes
Example unauthorized request:
- missing `X-Auth-Token`
- result: `401 Unauthorized`

Example forbidden request:
- `X-User-Role: student`
- result: `403 Forbidden`

Example authorized request:
- valid token
- `X-User-Role: teacher`
- result: `200 OK`

## Evidence
- PR link: (added after PR link is created)
- Demo note: protected endpoint now rejects unauthorized access server-side