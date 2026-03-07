#pragma once

#include "problem/subtraction_problem.h"
#include <string>
#include <vector>

/*
  @class SubtractionProblemGenerator
  @brief Responsible for creating multiple subtraction problems.

  Generates problems with:
   - 2 to 4 minuends
   - Random integers that range between the values set in subtraction_problem_generator.cpp
 */
class SubtractionProblemGenerator {
public:
  std::vector<SubtractionProblem> generateProblems(int numProblems, const std::string &difficulty);
};
