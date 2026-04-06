# Hand-Off Document Draft

## System Overview
This project is a semester-scale adaptive learning platform prototype focused on demonstrating a thin vertical slice that runs end-to-end. The system allows student creation, assessment submission, and rule-based recommendation generation while maintaining a strong emphasis on maintainability, reliability, and test coverage.

The implementation prioritizes clean structure, validation correctness, and automated testing over feature expansion. The goal is to ensure that the system can be easily understood, debugged, and extended by a future team.

---

## Stack and Tool Choices

- **Language:** C++17  
- **HTTP Library:** cpp-httplib  
- **Build System:** CMake  
- **Testing Framework:** CTest  
- **Formatting:** clang-format  
- **CI/CD:** GitHub Actions  
- **Storage:** In-memory store (prototype only)

### Why this stack was chosen
The stack was selected to support a lightweight, testable, and maintainable backend system that can run locally without complex dependencies. It also integrates cleanly with CI pipelines for automated grading and validation.

---

## Setup / Run Summary

### 1. Clone the repository
```bash
git clone https://github.com/Georgia-Southwestern-State-Univeristy/term-project-group-7.git
cd term-project-group-7