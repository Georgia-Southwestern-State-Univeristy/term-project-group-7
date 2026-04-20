# Week 15 Presentation Plan + Speaking Roles

## Purpose

This document defines the final presentation structure, speaking roles, demo responsibilities, and backup plan to ensure a clear and professional delivery of the project.

---

## Presentation Title

Adaptive Learning Platform Prototype for Middle-School Math

---

## Presentation Length

12–15 minutes

---

## Presentation Goal

Demonstrate a working system, explain key technical decisions, show final QA confidence, and communicate the project clearly and professionally.

---

## Presentation Structure

### 1. Introduction (1–2 minutes)

**Speaker:** David Hugee-James

* Project overview
* Problem being solved
* Goal of the system
* Why a thin vertical slice was chosen

---

### 2. Architecture Overview (2–3 minutes)

**Speaker:** Ridhwaan Jimoh

* System structure (GUI + API)
* Key components
* Data flow
* Design decisions and trade-offs

---

### 3. QA + System Readiness (1–2 minutes)

**Speaker:** Victor Grey

* Build/test/run verification
* Runtime requirements
* Stability of system
* Confidence from QA process

---

### 4. Live Demo (4–5 minutes)

**Demo Driver:** Victor Grey
**Support:** Ridhwaan Jimoh

#### Demo Steps

1. Launch application
2. Show main menu
3. Select grade
4. Choose math operation
5. Answer one question correctly
6. Answer one question incorrectly
7. Show hint functionality
8. Move to next question
9. Open analytics
10. Show health endpoint in browser

---

### 5. Documentation + Handoff (2–3 minutes)

**Speaker:** David Hugee-James

* Repository structure
* How a reviewer runs the project
* User/Admin documentation
* Handoff completeness

---

### 6. Closing + Next Steps (1 minute)

**Speaker:** David Hugee-James

* What was achieved
* Known limitations
* Future improvements

---

## Speaking Roles Summary

| Team Member       | Role                                 |
| ----------------- | ------------------------------------ |
| Victor Grey       | QA Lead + Demo Driver                |
| David Hugee-James | Project Lead + Documentation         |
| Ridhwaan Jimoh    | Architecture + Technical Explanation |

---

## Demo Responsibility

* **Primary Demo Driver:** Victor Grey
* **Backup Demo Support:** Ridhwaan Jimoh

---

## Backup Plan (If Demo Fails)

If the demo partially fails:

1. Explain intended demo flow clearly
2. Show QA checklist document
3. Show runbook instructions
4. Show health endpoint if GUI fails
5. Continue presentation without stopping

---

## Risks and Mitigation

### Risk: Missing runtime files

* Mitigation: Verify `questions.db` and `static/` before demo

### Risk: Application crash

* Mitigation: Follow rehearsed demo path only

### Risk: Time overrun

* Mitigation: Stick to planned sections and timing

---

## Presentation Evidence

* QA Document: `docs/final/week15-qa.md`
* Handoff Status: `docs/final/week15-handoff-status.md`
* Contributions: `docs/final/week15-contributions.md`
* PR: WEEK 15 PR LINK

---

## Final Notes

* Every member has a speaking role
* Demo path is rehearsed
* Backup plan is defined
* Presentation is structured and controlled
