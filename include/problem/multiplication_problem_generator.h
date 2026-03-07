#pragma once

#include "problem/multiplication_problem.h"
#include <string>
#include <vector>

/*
  @class MultiplicationProblemGenerator
  @brief Responsible for creating multiple multiplication problems.

  Generates problems with:
   - 2 to 3 multiplicands
   - Random integers that range between the values set in multiplication_problem_generator.cpp
 */
class MultiplicationProblemGenerator {
public:
  std::vector<MultiplicationProblem> generateProblems(int numProblems, const std::string &difficulty);
};
