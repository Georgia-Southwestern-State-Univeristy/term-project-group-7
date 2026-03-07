#include "problem/multiplication_problem_generator.h"
#include <random>

/*
  This file generates several multiplication problems when invoked.


  Each problem:
   - Contains between 2 multiplicand
   - Uses integer values in the range [0, 3000]
   - Stores the provided difficulty level

  @param numProblems  Number of problems to generate
  @param difficulty   Difficulty label associated with each problem

    future note: the difficulty level is present but not implemented. It seems
    that the difficulty level between 6th grade multiplication problems and 7th-8th
    is that 7th - 8th are multi-step problems in which multiplication may just be one of
    the steps. The problems being generated are representative of 6th grade multiplication
    problems with 7th and 8th being added in future versions when data persistence
    has been implemented.

  @return A vector containing the generated MultiplicationProblem objects
 */
std::vector<MultiplicationProblem>
MultiplicationProblemGenerator::generateProblems(int numProblems, const std::string &difficulty) {
  std::vector<MultiplicationProblem> problems;

  // Random number engine setup
  std::random_device randomDevice;        // Initial random seed pulled from the OS.
  std::mt19937 generator(randomDevice()); // True random number generator.

  // Determines how many minuends will be in each problem
  // Either 2, 3, or 4
  // std::uniform_int_distribution<> minuendsCountTotal(2, 4);

  // Determines the value of each multiplicand (0 to 3000)
  std::uniform_int_distribution<> valueDist(0, 3000);

  for (int i = 0; i < 2; ++i) {
    int multiplicandCount = 2;
    //multiplicandCountTotal(generator);
    // predetermine vector size to prevent future resizing
    std::vector<double> multiplicand;
    multiplicand.reserve(multiplicandCount);

    for (int j = 0; j < multiplicandCount; ++j) {
      multiplicand.push_back(valueDist(generator));
    }

    problems.emplace_back(multiplicand, difficulty);
  }

  return problems;
}
