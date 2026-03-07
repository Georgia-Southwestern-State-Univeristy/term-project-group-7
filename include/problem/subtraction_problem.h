#pragma once

#include <string>
#include <vector>

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
