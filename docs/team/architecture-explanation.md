# Architecture Overview

## Architectural Goals
- Simplicity and clarity
- Explainable learning decisions
- Feasible semester-scale prototype

## System Context
Describe who uses the system (students, teachers) and how they interact with it.

## Major Components
- Authentication & Roles
- Assessment Engine
- Rules-Based Adaptive Logic
- Content Delivery
- Teacher Dashboard

Explain what each does and why it exists.

## Data Flow
Walk through:
1. Student assessment submission
2. Scoring and proficiency evaluation
3. Learning path decision
4. Progress reporting to teachers

## Key Design Decisions
Reference ADR-001:
- Why rules-based logic was chosen
- Why ML/AI was deferred

## Trade-Offs and Limitations
- Simplicity vs personalization
- Local prototype vs scalable deployment
- Explainability vs sophistication

## Scalability & Change Considerations
- What could scale later (content, analytics)
- What would need redesign (ML engine, hosting)

## Summary
Why this architecture is appropriate *now*.
