# Week 11 End-to-End Workflow Proof

## Primary Workflow
Student creation → assessment submission → rules-based recommendation retrieval

## Why this is the primary workflow
This is the clearest complete workflow currently implemented in the system. It moves across multiple components and ends in a meaningful system result. It is more than a page load and more than a health check.

## Entry Point and User Role

**Entry point:**  
`POST /api/students`

**Primary user role:**  
Student-facing workflow initiated through the system API

**Follow-on endpoints used in the same workflow:**
- `POST /api/students/{studentId}/assessments`
- `GET /api/students/{studentId}/recommendations/latest`

## Major Components Involved

### 1. HTTP server
Implemented in `src/server.cpp`

The server:
- receives the HTTP request
- validates required body fields
- maps requests to service calls
- returns JSON responses and HTTP status codes
- writes structured logs for success and failure cases

### 2. MVP service layer
Implemented in `src/mvp_service.h`

The service:
- creates students
- validates grade level and score ranges
- creates assessments
- generates rules-based recommendations
- retrieves the latest recommendation for a student

### 3. In-memory store
Implemented in `src/in_memory_store.h`

The store:
- persists students in memory
- persists assessments in memory
- stores the latest recommendation per student

### 4. Rules-based recommendation logic
Implemented in `MvpService::make_rule_recommendation(...)`

Current rule behavior:
- score below 70 → `<skill>_foundations`
- score 70 or above → `<skill>_next`

## Start-to-Finish Workflow

### Step 1: Create student
**Endpoint:**  
`POST /api/students`

**Example request body:**
```json
{"name":"David","gradeLevel":7}