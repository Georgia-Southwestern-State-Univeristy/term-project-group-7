# Project Proposal

## Problem Statement + Target Users

**Problem Statement**  
According to recent statistical analysis, the average American student’s proficiency in mathematics has declined for the first time in decades. Gaps in foundational math skills place students at risk academically and threaten long-term success in STEM-related fields. Traditional classroom instruction often lacks the flexibility and individualized reinforcement needed to address these gaps effectively.

**Target Users**
- **Primary:** Middle school students (grades 6–8) who need supplemental math practice outside of traditional classroom instruction.
- **Secondary:** Educators (teachers and administrators) who need visibility into student progress and learning trends to better support instruction.

---

## Core Use Cases (3–6)

- **UC1 (Student – Assessment):** A student logs in and completes a short assessment to identify strengths and knowledge gaps.
- **UC2 (Student – Learning Path):** A student receives a personalized learning path based on assessment results.
- **UC3 (Student – Practice & Feedback):** A student completes lessons and short exercises and receives immediate formative feedback.
- **UC4 (Teacher – Monitoring):** A teacher logs in to view individual student progress and proficiency levels.
- **UC5 (Teacher – Trend Analysis):** A teacher views aggregated performance data to identify common areas of difficulty and adjust instruction accordingly.

---

## Must-Have Features for the Week 8 Prototype

**Student Functionality**
- Secure account authentication with student-level permissions
- Personalized learning path based on assessment performance
- Ability to complete lessons and short assessments
- Immediate feedback on exercises and assessments

**Teacher / Administrator Functionality**
- Role-based authentication with elevated permissions
- Ability to view individual and aggregated student progress
- Basic dashboard displaying performance trends and deficiencies

**System-Level Features**
- Support for mathematics instruction for grades 6–8
- Instruction limited to a subset of content from one grade level
- Clear separation of student and teacher access rights

---

## Non-Goals (Explicitly Out of Scope)

- Replacing existing school curricula or standardized assessment systems
- Full curriculum coverage for grades 6–8
- Support for students enrolled in Individualized Education Programs (IEPs)
- Advanced analytics, predictive modeling, or AI-driven tutoring
- Integration with external learning management systems (e.g., Canvas, Google Classroom)
- Parent-facing accounts or features
- Mobile application development
- Deployment as a publicly accessible web-based platform

---

## Assumptions & Constraints

### Assumptions
- Content is instructor-created and limited to selected math topics
- Users consist of limited test users or simulated student data
- The prototype demonstrates instructional workflow rather than full curriculum coverage

### Constraints
- **Time:** One academic semester development timeline
- **Team Size:** Small development team with defined roles
- **Technology Limits:** No machine learning or advanced analytics
- **Data/Content:** Limited dataset and select instructional topics only

---

## Risks (Technical + Scope + Team)

### Technical Risks
- Improper authentication could expose teacher-only features to students  
  *Mitigation:* Role-based access controls and testing.
- Assessment scoring errors could misrepresent student understanding  
  *Mitigation:* Simple, testable scoring rules and validation.
- Dashboard visualizations may oversimplify learning trends  
  *Mitigation:* Limit metrics to clearly defined and verifiable indicators.

### Scope Risks
- Attempting to expand toward full curriculum coverage  
  *Mitigation:* Strict feature prioritization and clearly defined non-goals.
- Overengineering analytics beyond prototype needs  
  *Mitigation:* Focus on core learning functionality only.

### Team Risks
- Uneven contributions or PR delays  
  *Mitigation:* Clear team charter expectations, weekly sync meetings, and enforced PR review rules.

---

## Summary

This project delivers a focused and feasible educational software prototype that demonstrates how personalized learning paths and performance visibility can enhance middle school mathematics education. The scope is intentionally constrained to ensure that a complete, functional system can be delivered, reviewed, and evaluated within the semester timeline.
