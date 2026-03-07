#include <iostream>
#include <limits>

#include "menu/subtraction_menu.h"
#include "problem/subtraction_problem_generator.h"

/*
  This file offers the subtraction selection of the program. it presents
  users with a submenu of subtraction problem types such as integer,
  decimals, fractions, mixed operations, and back. The back option
  returns the user to the main menu.
 */
void displaySubtractionMenuOptions() {
  std::cout << "\n---- SUBTRACTION MENU ----\n";
  std::cout << "1. Integers\n";
  std::cout << "2. Decimals\n";
  std::cout << "3. Fractions\n";
  std::cout << "4. Mixed\n";
  std::cout << "0. Back\n";
}

/*
  Runs the subtraction submenu loop.

  The user can:
   - Select integer problems
   - Answer each question one at a time
   - Receive immediate feedback (correct, incorrect, score)
 */
void runSubtractionMenu() {

  while (true) {

    displaySubtractionMenuOptions();

    int selection;
    std::cin >> selection;

    // Catches invalid input from the user.
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (selection == 0) {
      break;
    }

    switch (selection) {

    case 1: {
      std::cout << "\nInteger quiz selected.\n";

      SubtractionProblemGenerator generator;

      // Hardcoded to 3 problems for now
      std::vector<SubtractionProblem> problems = generator.generateProblems(3, "6-8 grade");

      int score = 0;

      for (size_t i = 0; i < problems.size(); ++i) {

        std::cout << "\nProblem " << (i + 1) << ": " << problems[i].problemText << " = ?\n";

        int userAnswer;

        // Ensure only integer input
        while (!(std::cin >> userAnswer)) {
          std::cout << "Please enter a valid integer: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (userAnswer == static_cast<int>(problems[i].answer)) {

          std::cout << "Correct!\n";
          score++;
        } else {
          std::cout << "Incorrect.\n";
        }
      }

      std::cout << "\nQuiz complete.\n";
      std::cout << "Final Score: " << score << " / " << problems.size() << "\n";

      break;
    }

    case 2:
      std::cout << "Decimal operations not implemented yet.\n";
      break;

    case 3:
      std::cout << "Fraction operations not implemented yet.\n";
      break;

    case 4:
      std::cout << "Mixed operations not implemented yet.\n";
      break;

    default:
      std::cout << "Invalid selection.\n";
    }
  }
}
