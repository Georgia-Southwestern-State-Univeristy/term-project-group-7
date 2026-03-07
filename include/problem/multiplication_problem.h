#pragma once

#include <string>
#include <vector>

/*
  @class MultiplicationProblem
  @brief Represents a single multiplication problem.

  This class stores:
   - The multiplicand (2–3 numbers)
   - A text version of the problem (e.g., "2 x 3 x 4")
   - The computed answer
   - The difficulty label

  The answer and problem text are generated
  when the object is constructed.

  future notes: this file needs to be expanded to include word problems.
 */
class MultiplicationProblem {
public:
  std::vector<double> multiplicand; // A dynamic array containing the minuends.
                                    // Using a vector allows for the individual problem objects to
                                    // range between adding 2 to 3 values with ease.

  std::string problemText; // The multiplication problem converted to a string for display
  double answer;           // The product
  std::string difficulty;  // The grade level 6th - 8th (Note: difficulty not implemented)

  // The MultiplicationProblem constructor.
  MultiplicationProblem(const std::vector<double> &inputMultiplicand,
                        const std::string &inputDifficulty);

private:
  void generateProblemText();
  void computeAnswer();
};
