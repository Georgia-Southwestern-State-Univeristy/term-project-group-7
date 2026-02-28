#include "problem/addition_problem_generator.h"
#include <random>

/*
  This file generates several addition problems when invoked.

 
  Each problem:
   - Contains between 2 and 4 addends
   - Uses integer values in the range [-100, 1000]
   - Stores the provided difficulty level
 
  @param numProblems  Number of problems to generate
  @param difficulty   Difficulty label associated with each problem

    future note: the difficulty level is present but not implemented. It seems
    that the difficulty level between 6th grade addition problems and 7th-8th
    is that 7th - 8th are multi-step problems in which addition may just be one of
    the steps. The problems being generated are representative of 6th grade addition
    problems with 7th and 8th being added in future versions when data persistence
    has been implemented.
 
  @return A vector containing the generated AdditionProblem objects
 */
std::vector<AdditionProblem>
AdditionProblemGenerator::generateProblems(int numProblems, const std::string &difficulty) {
  std::vector<AdditionProblem> problems;

  // Random number engine setup
  std::random_device randomDevice; //Initial random seed pulled from the OS.
  std::mt19937 generator(randomDevice()); //True random number generator.

  // Determines how many addends will be in each problem
  // Either 2, 3, or 4
  std::uniform_int_distribution<> addendsCountTotal(2, 4);

  // Determines the value of each addend (-100 to 1000)
  std::uniform_int_distribution<> valueDist(-100, 1000);

  for (int i = 0; i < numProblems; ++i) {
    int addendCount = addendsCountTotal(generator);
    //predetermine vector size to prevent future resizing
    std::vector<double> addends;
    addends.reserve(addendCount); 

    for (int j = 0; j < addendCount; ++j) {
      addends.push_back(valueDist(generator));
    }

    problems.emplace_back(addends, difficulty);
  }

  return problems;
}
