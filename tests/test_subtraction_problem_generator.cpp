#include "problem/subtraction_problem.h"
#include "problem/subtraction_problem_generator.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic tests for the SubtractionProblemGenerator.

  This test verifies that:
   - The correct number of problems is generated
   - Each problem contains a reasonable number of minuends
   - The answer stored in each problem is accurate
   - The difficulty string is passed through correctly

  Since the generator uses randomness, we don't check exact values —
  only structural correctness and internal consistency.
 */
void testSubtractionProblemGenerator() {

  SubtractionProblemGenerator generator;

  const int requestedProblems = 5;
  const std::string difficultyLevel = "6-8 grade";

  // Generate a batch of problems
  std::vector<SubtractionProblem> problems =
      generator.generateProblems(requestedProblems, difficultyLevel);

  // ---- Check number of problems generated ----
  assert(problems.size() == requestedProblems);

  // ---- Validate each generated problem ----
  for (const auto &problem : problems) {

    // Ensure addend count is within expected bounds (2–4)
    assert(problem.minuends.size() >= 2);
    assert(problem.minuends.size() <= 4);

    // Verify the answer matches the difference of minuends
    double computedDifference = problem.minuends[0];
    for (size_t i = 1; i < problem.minuends.size(); ++i) {
      computedDifference -= problem.minuends[i];
    }

    assert(problem.answer == computedDifference);

    // Ensure difficulty was preserved
    assert(problem.difficulty == difficultyLevel);

    // Ensure problem text is not empty
    assert(!problem.problemText.empty());
  }

  std::cout << "PASS: /SubtractionProblemGenerator/health OK\n";
}
