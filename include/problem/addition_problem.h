#pragma once

#include <string>
#include <vector>

/*
  @class AdditionProblem
  @brief Represents a single addition problem.
 
  This class stores:
   - The addends (2–4 numbers)
   - A text version of the problem (e.g., "5 + 3 + 2")
   - The computed answer
   - The difficulty label
 
  The answer and problem text are generated
  when the object is constructed.
  
  future notes: this file needs to be expanded to include word problems.
 */
class AdditionProblem {
public:
  std::vector<double> addends;  // A dynamic array containing the addends. 
								// Using a vector allows for the individual problem objects to
								// range between adding 2 to 4 values with ease.

  std::string problemText;      // The addition problem converted to a string for display 
  double answer;                // The sum
  std::string difficulty;       // The grade level 6th - 8th (Note: difficulty not implemented)

  //The AdditionProblem constructor.
  AdditionProblem(const std::vector<double> &inputAddends, const std::string &inputDifficulty);

private:
  void generateProblemText();
  void computeAnswer();
};
