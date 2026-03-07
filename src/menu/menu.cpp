#include <iostream>
#include <string>

#include "menu/addition_menu.h"
#include "menu/subtraction_menu.h"
#include "menu/multiplication_menu.h"
#include "menu/menu.h"

/*
  This file is the menu system for the math program.
  it displays the options addition, subtraction,
  multplication, division, and back. It takes in user input
  and only responds to the the values 0 - 4. All other options
  are treated as invalid input.
*/

void displayMainMenuOptions() {
  std ::cout << "\n----MAIN MENU----\n";
  std ::cout << "Select 1 for Addition\n";
  std ::cout << "Select 2 for Subtraction\n";
  std ::cout << "Select 3 for Multiplication\n";
  std ::cout << "Select 4 for Division\n";
  std ::cout << "Select 0 to Exit\n";
}

void runMainMenu() {
  while (true) {
    displayMainMenuOptions();

    std::string math_operation;

    int user_selection;
    std::cin >> user_selection;

    if (user_selection == 0) {
      break; // Exit the menu and start the server.
    }

    switch (user_selection) {
    case 1:
      runAdditionMenu();
      break;
    case 2:
      runSubtractionMenu();
      break;
    case 3:
      runMultiplicationMenu();
      break;
    case 4:
      std::cout << "\nMenu coming soon.\n";
      break;
    default:
      std::cout << "\nInvalid selection. Please try again.\n";
      continue;
    }
  }
}