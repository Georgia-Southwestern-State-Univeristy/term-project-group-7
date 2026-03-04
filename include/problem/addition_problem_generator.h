#pragma once

#include "problem/addition_problem.h"
#include <string>
#include <vector>

/*
  @class AdditionProblemGenerator
  @brief Responsible for creating multiple addition problems.

  Generates problems with:
   - 2 to 4 operands
   - Random integers that range between the values set in addition_problem_generator.cpp
 */
class AdditionProblemGenerator {
public:
  std::vector<AdditionProblem> generateProblems(int numProblems, const std::string &difficulty);
};
