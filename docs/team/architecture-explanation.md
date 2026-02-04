# Architecture Explanation (Team)

## Architecture Overview
This system is a semester-scale prototype of an adaptive learning platform for grades 6–8. It uses assessments plus rules-based logic to recommend content, track progress, and support teacher visibility.

## Architectural Goals
- **Simplicity and clarity:** reduce moving parts so the team can implement and test reliably this semester.
- **Explainable learning decisions:** recommendations must be understandable and defensible to teachers/students.
- **Feasible prototype scope:** local-first / minimal infrastructure so the project can ship a working beta.

## System Context
**Students** take assessments and receive recommended learning content.  
**Teachers** monitor progress, view analytics, and identify struggling topics.

Primary interactions:
- Student: login → take assessment → receive learning path/content → continue learning
- Teacher: login → view dashboards → review student performance → guide interventions

## Major Components

### Authentication & Roles
Handles login and role-based access (student vs teacher). Prevents teacher features from being exposed to students.

### Assessment Engine
Delivers assessments, collects answers, scores submissions, and stores results.

### Rules-Based Adaptive Logic
Interprets proficiency (based on rules/thresholds) and decides the next learning step. This is intentionally transparent.

### Content Delivery
Presents the recommended lessons/practice for a student based on the learning path decision.

### Teacher Dashboard
Aggregates student performance, trends, and topic mastery for teacher review.

## Data Flow
1. **Student assessment submission:** Student completes an assessment and submits answers.
2. **Scoring and proficiency evaluation:** Assessment Engine scores and calculates proficiency (e.g., by topic/skill).
3. **Learning path decision:** Rules-Based Logic selects next content based on proficiency thresholds and progress history.
4. **Progress reporting:** Results and progress summaries are stored and displayed in the Teacher Dashboard.

## Key Design Decisions (ADR Reference)
This architecture follows **ADR-0001** (Rules-Based Adaptive Engine).
- **Why rules-based logic was chosen:** explainable decisions, fast implementation, predictable behavior.
- **Why ML/AI was deferred:** insufficient training data, higher complexity, higher risk for semester scope.

## Trade-Offs and Limitations
- **Simplicity vs personalization:** rules are less “smart” than ML but are easier to validate.
- **Local prototype vs scalable deployment:** local DB + single deployment is simpler; scaling requires new infrastructure.
- **Explainability vs sophistication:** we prioritize transparency over black-box optimization.

## Scalability & Change Considerations
**Could scale later:**
- Content library expansion
- More analytics views and teacher tools

**Would need redesign:**
- ML personalization engine (data pipeline, model training, evaluation, governance)
- Hosting architecture (multi-user concurrency, cloud DB, authentication hardening)

## Summary
This architecture is appropriate now because it supports a working, explainable prototype within a semester while leaving clear paths for future growth (scaling content/analytics and migrating to hosted infrastructure later).

