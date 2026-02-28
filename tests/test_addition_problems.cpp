#include "problem/addition_problem.h"

#include <cassert>
#include <iostream>
#include <vector>

/*
  Basic tests for the AdditionProblem class.
 
  This test creates a simple addition problem and verifies:
   - The addends are stored correctly
   - The generated problem text matches expectations
   - The computed answer is correct
   - The difficulty string is preserved
 
  These are straightforward sanity checks to make sure the
  constructor initializes everything properly.
 */
void testAdditionProblem() {
  //std::cout << "\n--- Running AdditionProblem tests ---\n";

  // Sample data for the test
  std::vector<double> numbers = {3, 5, 7};
  std::string difficultyLevel = "6-8 grade";

  // Construct the problem
  AdditionProblem problem(numbers, difficultyLevel);

  // ---- Check addends ----
  assert(problem.addends.size() == numbers.size());

  for (size_t i = 0; i < numbers.size(); ++i) {
    assert(problem.addends[i] == numbers[i]);
  }

  // ---- Check problem text formatting ----
  // We expect something like "3 + 5 + 7"
  std::string expectedText = "3 + 5 + 7";
  assert(problem.problemText == expectedText);

  // ---- Check computed answer ----
  double calculatedSum = 0.0;
  for (double value : numbers) {
    calculatedSum += value; // manually compute sum for comparison
  }

  assert(problem.answer == calculatedSum);

  // ---- Check difficulty storage ----
  assert(problem.difficulty == difficultyLevel);

  std::cout << "PASS: /AdditionProblem/health OK\n";
}
