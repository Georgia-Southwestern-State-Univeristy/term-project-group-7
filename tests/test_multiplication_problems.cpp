#include "problem/multiplication_problem.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic tests for the MultiplicationProblem class.

  This test creates a simple multiplication problem and verifies:
   - The multiplicand are stored correctly
   - The generated problem text matches expectations
   - The computed answer is correct
   - The difficulty string is preserved

  These are straight forward sanity checks to make sure the
  constructor initializes everything properly.
 */
void testMultiplicationProblem() {

  // Sample data for the test
  std::vector<double> numbers = {101, 11};
  std::string difficultyLevel = "6-8 grade";

  // Construct the problem
  MultiplicationProblem problem(numbers, difficultyLevel);

  // ---- Check multiplicands ----
  assert(problem.multiplicand.size() == numbers.size());

  for (size_t i = 0; i < numbers.size(); ++i) {
    assert(problem.multiplicand[i] == numbers[i]);
  }

  // ---- Check problem text formatting ----
  // We expect something like "101 x 11"
  std::string expectedText = "101 x 11";
  assert(problem.problemText == expectedText);

  // ---- Check computed answer ----
  double calculatedProduct = problem.multiplicand[0];
  for (size_t i = 1; i < problem.multiplicand.size(); ++i) {
    calculatedProduct *= problem.multiplicand[i]; // manually compute product for comparison
  }

  assert(problem.answer == calculatedProduct);

  // ---- Check difficulty storage ----
  assert(problem.difficulty == difficultyLevel);

  std::cout << "PASS: /MultiplicationProblem/health OK\n";
}
