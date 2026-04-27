# Final Technical Defense

## Why This Architecture and Stack?

The system uses a lightweight C++ backend with a REST API to ensure performance, simplicity, and control over system behavior. C++ was selected to demonstrate lower-level system understanding, while CMake and CTest provide a structured build and testing workflow.

---

## Key Technical Trade-Offs

* **Rules-Based Logic vs Machine Learning**

  * Chosen for simplicity and explainability
  * Trade-off: less personalization

* **Local Deployment vs Cloud**

  * Easier to implement and test
  * Trade-off: not production scalable

* **Minimal Frontend**

  * Focus placed on backend system design
  * Trade-off: limited user interaction

---

## Biggest Current Weakness

The system lacks advanced personalization and scalability. The rule-based approach limits adaptability compared to modern AI-driven systems.

---

## Testing and CI Confidence

Confidence is supported by:

* Automated tests using CTest
* Continuous Integration via GitHub Actions
* Successful build and test validation on every commit

---

## If Another Team Took Over

The next team should prioritize:

1. Implementing a machine learning recommendation system
2. Adding authentication and user roles
3. Building a frontend interface
4. Deploying to a cloud environment
5. Expanding test coverage and performance validation

---

## Summary

The system demonstrates strong engineering fundamentals, clear architecture, and a stable foundation for future expansion.
