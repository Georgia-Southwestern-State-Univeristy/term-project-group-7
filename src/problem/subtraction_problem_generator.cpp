#include "problem/subtraction_problem_generator.h"
#include <random>

/*
  This file generates several subtraction problems when invoked.


  Each problem:
   - Contains between 2 and 4 minuends
   - Uses integer values in the range [-100, 1000]
   - Stores the provided difficulty level

  @param numProblems  Number of problems to generate
  @param difficulty   Difficulty label associated with each problem

    future note: the difficulty level is present but not implemented. It seems
    that the difficulty level between 6th grade subtraction problems and 7th-8th
    is that 7th - 8th are multi-step problems in which subtraction may just be one of
    the steps. The problems being generated are representative of 6th grade subtraction
    problems with 7th and 8th being added in future versions when data persistence
    has been implemented.

  @return A vector containing the generated SubtractionProblem objects
 */
std::vector<SubtractionProblem>
SubtractionProblemGenerator::generateProblems(int numProblems, const std::string &difficulty) {
  std::vector<SubtractionProblem> problems;

  // Random number engine setup
  std::random_device randomDevice;        // Initial random seed pulled from the OS.
  std::mt19937 generator(randomDevice()); // True random number generator.

  // Determines how many minuends will be in each problem
  // Either 2, 3, or 4
  std::uniform_int_distribution<> minuendsCountTotal(2, 4);

  // Determines the value of each minuend (-100 to 1000)
  std::uniform_int_distribution<> valueDist(-100, 1000);

  for (int i = 0; i < numProblems; ++i) {
    int minuendCount = minuendsCountTotal(generator);
    // predetermine vector size to prevent future resizing
    std::vector<double> minuends;
    minuends.reserve(minuendCount);

    for (int j = 0; j < minuendCount; ++j) {
      minuends.push_back(valueDist(generator));
    }

    problems.emplace_back(minuends, difficulty);
  }

  return problems;
}
