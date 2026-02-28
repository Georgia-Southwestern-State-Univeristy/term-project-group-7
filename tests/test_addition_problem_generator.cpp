#include "problem/addition_problem.h"
#include "problem/addition_problem_generator.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic tests for the AdditionProblemGenerator.
 
  This test verifies that:
   - The correct number of problems is generated
   - Each problem contains a reasonable number of addends
   - The answer stored in each problem is accurate
   - The difficulty string is passed through correctly
 
  Since the generator uses randomness, we don't check exact values —
  only structural correctness and internal consistency.
 */
void testAdditionProblemGenerator() {
  //std::cout << "\n--- Running AdditionProblemGenerator tests ---\n";

  AdditionProblemGenerator generator;

  const int requestedProblems = 5;
  const std::string difficultyLevel = "6-8 grade";

  // Generate a batch of problems
  std::vector<AdditionProblem> problems =
      generator.generateProblems(requestedProblems, difficultyLevel);

  // ---- Check number of problems generated ----
  assert(problems.size() == requestedProblems);

  // ---- Validate each generated problem ----
  for (const auto &problem : problems) {

    // Ensure addend count is within expected bounds (2–4)
    assert(problem.addends.size() >= 2);
    assert(problem.addends.size() <= 4);

    // Verify the answer matches the sum of addends
    double computedSum = 0.0;
    for (double value : problem.addends) {
      computedSum += value;
    }

    assert(problem.answer == computedSum);

    // Ensure difficulty was preserved
    assert(problem.difficulty == difficultyLevel);

    // Ensure problem text is not empty
    assert(!problem.problemText.empty());
  }

  std::cout << "PASS: /AdditionProblemGenerator/health OK\n";
}
