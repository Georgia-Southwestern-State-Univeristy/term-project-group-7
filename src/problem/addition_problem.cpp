#include "problem/addition_problem.h"
#include <sstream>
/*
  This is the implementation file for the addition_problem.h file.
  This file is responsible for taking an array of numbers
  and difficulty rating and creating an addition problem
  object. It computes the answer and builds a string for
  displaying the problem to the user.
*/

/*
  Constructor
  Stores addends and difficulty, then builds
  the problem text and computes the answer.
 */
AdditionProblem::AdditionProblem(const std::vector<double> &inputAddends,
                                 const std::string &inputDifficulty)
    : addends(inputAddends), difficulty(inputDifficulty), answer(0.0) {
  computeAnswer();
  generateProblemText();
}

/*
  Computes the sum of all addends.
 */
void AdditionProblem::computeAnswer() {
  answer = 0.0;

  for (size_t i = 0; i < addends.size(); ++i) {
    answer += addends[i];
  }
}

/*
  Builds a readable string like:
  "5 + 3 + 2"
 */
void AdditionProblem::generateProblemText() {
  std::ostringstream oss;

  for (size_t i = 0; i < addends.size(); ++i) {
    oss << static_cast<int>(addends[i]);

    // Add "+" between numbers
    if (i != addends.size() - 1) {
      oss << " + ";
    }
  }

  problemText = oss.str();
}
