#include "problem/multiplication_problem.h"
#include <sstream>
/*
  This is the implementation file for the multiplication_problem.h file.
  This file is responsible for taking an array of numbers
  and difficulty rating and creating an multiplication problem
  object. It computes the answer and builds a string for
  displaying the problem to the user.
*/

/*
  Constructor
  Stores multiplicands and difficulty, then builds
  the problem text and computes the answer.
 */
MultiplicationProblem::MultiplicationProblem(const std::vector<double> &inputMultiplicands,
                                       const std::string &inputDifficulty)
    : multiplicand(inputMultiplicands), difficulty(inputDifficulty), answer(0.0) {
  computeAnswer();
  generateProblemText();
}

/*
  Computes the product of all multiplicands.
 */
int answer = 1;
void MultiplicationProblem::computeAnswer() {
  answer = multiplicand[0];

  for (size_t i = 1; i < multiplicand.size(); ++i) {
    answer *= multiplicand[i];
  }
}

/*
  Builds a readable string like:
  "2 x 3 x 4"
 */
void MultiplicationProblem::generateProblemText() {
  std::ostringstream oss;

  for (size_t i = 0; i < multiplicand.size(); ++i) {
    oss << static_cast<int>(multiplicand[i]);

    // Add "x" between numbers
    if (i != multiplicand.size() - 1) {
      oss << " x ";
    }
  }

  problemText = oss.str();
}
