#include "problem/subtraction_problem.h"
#include <sstream>
/*
  This is the implementation file for the subtraction_problem.h file.
  This file is responsible for taking an array of numbers
  and difficulty rating and creating an subtraction problem
  object. It computes the answer and builds a string for
  displaying the problem to the user.
*/

/*
  Constructor
  Stores minuends and difficulty, then builds
  the problem text and computes the answer.
 */
SubtractionProblem::SubtractionProblem(const std::vector<double> &inputMinuends,
                                       const std::string &inputDifficulty)
    : minuends(inputMinuends), difficulty(inputDifficulty), answer(0.0) {
  computeAnswer();
  generateProblemText();
}

/*
  Computes the sum of all minuends.
 */
void SubtractionProblem::computeAnswer() {
  answer = minuends[0];

  for (size_t i = 1; i < minuends.size(); ++i) {
    answer -= minuends[i];
  }
}

/*
  Builds a readable string like:
  "10 - 17 - -8"
 */
void SubtractionProblem::generateProblemText() {
  std::ostringstream oss;

  for (size_t i = 0; i < minuends.size(); ++i) {
    oss << static_cast<int>(minuends[i]);

    // Add "-" between numbers
    if (i != minuends.size() - 1) {
      oss << " - ";
    }
  }

  problemText = oss.str();
}
