#pragma once

#include <string>
#include <vector>

/*
  @class SubtractionProblem
  @brief Represents a single subtraction problem.

  This class stores:
   - The minuends (2–4 numbers)
   - A text version of the problem (e.g., "10 - 3 - 5")
   - The computed answer
   - The difficulty label

  The answer and problem text are generated
  when the object is constructed.

  future notes: this file needs to be expanded to include word problems.
 */
class SubtractionProblem {
public:
  std::vector<double> minuends; // A dynamic array containing the minuends.
                                // Using a vector allows for the individual problem objects to
                                // range between adding 2 to 4 values with ease.

  std::string problemText; // The subtraction problem converted to a string for display
  double answer;           // The difference
  std::string difficulty;  // The grade level 6th - 8th (Note: difficulty not implemented)

  // The SubtractionProblem constructor.
  SubtractionProblem(const std::vector<double> &inputMinuends, const std::string &inputDifficulty);

private:
  void generateProblemText();
  void computeAnswer();
};
