#include "problem/subtraction_problem.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic tests for the SubtractionProblem class.

  This test creates a simple subtraction problem and verifies:
   - The minueds are stored correctly
   - The generated problem text matches expectations
   - The computed answer is correct
   - The difficulty string is preserved

  These are straightforward sanity checks to make sure the
  constructor initializes everything properly.
 */
void testSubtractionProblem() {

  // Sample data for the test
  std::vector<double> numbers = {10, 17, -8};
  std::string difficultyLevel = "6-8 grade";

  // Construct the problem
  SubtractionProblem problem(numbers, difficultyLevel);

  // ---- Check minuends ----
  assert(problem.minuends.size() == numbers.size());

  for (size_t i = 0; i < numbers.size(); ++i) {
    assert(problem.minuends[i] == numbers[i]);
  }

  // ---- Check problem text formatting ----
  // We expect something like "10 - 17 - -8"
  std::string expectedText = "10 - 17 - -8";
  assert(problem.problemText == expectedText);

  // ---- Check computed answer ----
  double calculatedDifference = problem.minuends[0];
  for (size_t i = 1; i < problem.minuends.size(); ++i) {
    calculatedDifference -= problem.minuends[i]; // manually compute difference for comparison
  }

  assert(problem.answer == calculatedDifference);

  // ---- Check difficulty storage ----
  assert(problem.difficulty == difficultyLevel);

  std::cout << "PASS: /SubtractionProblem/health OK\n";
}
