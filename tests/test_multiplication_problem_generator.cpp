#include "problem/multiplication_problem.h"
#include "problem/multiplication_problem_generator.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic test for the MultiplicationProblemGenerator.

  This test verifies that:
   - The correct number of problems is generated
   - Each problem contains a reasonable number of minuends
   - The answer stored in each problem is accurate
   - The difficulty string is passed through correctly

  Since the generator uses randomness, we don't check exact values —
  only structural correctness and internal consistency.
 */
void testMultiplicationProblemGenerator() {

  MultiplicationProblemGenerator generator;

  const int requestedProblems = 2;
  const std::string difficultyLevel = "6-8 grade";

  // Generate a batch of problems
  std::vector<MultiplicationProblem> problems =
      generator.generateProblems(requestedProblems, difficultyLevel);

  // ---- Check number of problems generated ----
  assert(problems.size() == requestedProblems);

  // ---- Validate each generated problem ----
  for (const auto &problem : problems) {

    // Ensure multiplicand count is equal to the expected
    assert(problem.multiplicand.size() == 2);

    // Verify the answer matches the product of multiplicand
    double computedProduct = problem.multiplicand[0];
    for (size_t i = 1; i < problem.multiplicand.size(); ++i) {
      computedProduct *= problem.multiplicand[i];
    }

    assert(problem.answer == computedProduct);

    // Ensure difficulty was preserved
    assert(problem.difficulty == difficultyLevel);

    // Ensure problem text is not empty
    assert(!problem.problemText.empty());
  }

  std::cout << "PASS: /MultiplicationProblemGenerator/health OK\n";
}
