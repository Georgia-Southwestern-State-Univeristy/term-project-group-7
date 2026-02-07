# Architecture Explanation (Team)

## Architecture Overview
This system is a semester-scale prototype of an adaptive learning platform for grades 6–8. It uses assessments combined with rules-based adaptive logic to recommend learning content, track student progress, and provide visibility into performance for teachers and administrators.

This architecture is documented using a C4-style container diagram (see `Architecture_Diagram_C4.pdf`). The components and interactions described below directly correspond to the elements shown in that diagram.

## Architectural Goals
- **Simplicity and clarity:** Reduce moving parts so the team can implement and test reliably within a single semester.
- **Explainable learning decisions:** Recommendations must be understandable and defensible to teachers and students.
- **Feasible prototype scope:** Local-first design with minimal infrastructure so the project can ship a working beta.

## System Context
The system supports three primary user roles: students, teachers, and administrators.

- **Students** take assessments and receive recommended learning content based on demonstrated proficiency.
- **Teachers** monitor student progress, view analytics, and identify struggling topics in order to guide interventions.
- **Administrators** manage system configuration, content availability, and high-level oversight, but do not participate directly in student learning flows.

### Primary Interactions
- **Student:** login → take assessment → receive learning path/content → continue learning  
- **Teacher:** login → view dashboards → review student performance → guide interventions  
- **Administrator:** login → manage configuration and content metadata

## Major Components
- Authentication & Roles  
- Learning and Assessment Module  
- Rules-Based Adaptive Logic  
- Content Delivery  
- Analytics Module (Teacher Dashboard)  
- Embedded SQLite Database  

### Authentication & Roles
Handles login and role-based access control (student vs teacher vs administrator). Prevents privileged features from being exposed to unauthorized users.

### Learning and Assessment Module
Delivers assessments, collects student responses, scores submissions, and persists assessment results.

### Rules-Based Adaptive Logic
Interprets proficiency using predefined rules and thresholds and determines the next learning step. This logic is intentionally transparent to support explainability.

### Content Delivery
Presents recommended lessons or practice activities to students based on the selected learning path.

### Analytics Module (Teacher Dashboard)
Aggregates student performance data, trends, and topic mastery for teacher and administrator review.

### Embedded SQLite Database
Stores assessment results, proficiency scores, content metadata, and progress summaries for the local prototype deployment.

## Data Flow
1. **Student assessment submission:** A student completes an assessment and submits responses.
2. **Scoring and proficiency evaluation:** The Learning and Assessment Module scores responses and calculates proficiency (e.g., by topic or skill).
3. **Learning path decision:** Rules-Based Adaptive Logic selects the next content based on proficiency thresholds and progress history.
4. **Progress reporting:** Results and summaries are stored in the Embedded SQLite Database and displayed through the Analytics Module.

## Key Design Decisions (ADR Reference)
This architecture follows **ADR-0001 (Rules-Based Adaptive Engine)**.

- **Why rules-based logic was chosen:** It enables explainable decisions, fast implementation, and predictable behavior suitable for a semester-scale project.
- **Why ML/AI was deferred:** Insufficient training data, higher implementation complexity, and increased risk relative to the project timeline.

## Trade-Offs and Limitations
- **Simplicity vs personalization:** Rules are less adaptive than ML but easier to validate and explain.
- **Local prototype vs scalable deployment:** A local database and single deployment simplify development; scaling requires new infrastructure.
- **Explainability vs sophistication:** The system prioritizes transparency over black-box optimization.

## Scalability & Change Considerations
The current architecture intentionally optimizes for single-class, single-instance use during the semester and does not attempt to solve multi-tenant or large-scale deployment concerns.

### Could Scale Later
- Content library expansion  
- Additional analytics views and teacher tools  

### Would Need Redesign
- ML-based personalization engine (data pipelines, model training, evaluation, governance)
- Hosting architecture (multi-user concurrency, cloud database, authentication hardening)

## Summary
This architecture is appropriate now because it supports a working, explainable prototype within a semester while leaving clear paths for future growth, including scaling content and analytics and migrating to hosted infrastructure later.
