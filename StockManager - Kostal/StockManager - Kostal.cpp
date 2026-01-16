#include <iostream>
#include <string>
#include "ProductHandler.h"

void clearScreen() {
	system("cls");
}

void pauseScreen() {
	std::cout << " Press Enter to continue..." << std::endl;
	std::string dummy;
	std::getline(std::cin, dummy);
	if (dummy.empty() && std::cin.peek() == '\n') {
		std::cin.ignore();
	}
}

void showMenu() {
	std::cout << "****************************************" << std::endl;
	std::cout << "*        PRODUCT STOCK MANAGER         *" << std::endl;
	std::cout << "****************************************" << std::endl;
	std::cout << "* Please choose an option between 1-6: *" << std::endl;
	std::cout << "*--------------------------------------*" << std::endl;
	std::cout << "* 1. Add new product                   *" << std::endl;
	std::cout << "* 2. Search for a product              *" << std::endl;
	std::cout << "* 3. View all products                 *" << std::endl;
	std::cout << "* 4. Update product quantity           *" << std::endl;
	std::cout << "* 5. Remove a product                  *" << std::endl;
	std::cout << "* 6. Exit                              *" << std::endl;
	std::cout << "****************************************" << std::endl;
	std::cout << "Your choice: ";
}

void run() {
	ProductHandler handler(FILE_NAME);
	while (true) {
		clearScreen();
		showMenu();
		int choice;
		std::cin >> choice;
		while (true) {
			if (std::cin.fail() || choice > 6 || choice < 1) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input! Please enter a number between 1 and 6." << std::endl;
				std::cout << "Your choice: ";
				std::cin >> choice;
				continue;
			}
			break;
		}

		switch (choice) {
		case 1:
			clearScreen();
			handler.addProduct();
			pauseScreen();
			break;
		case 2:
			clearScreen();
			handler.findProduct();
			pauseScreen();
			break;
		case 3:
			clearScreen();
			handler.viewAllProducts();
			pauseScreen();
			break;
		case 4:
			clearScreen();
			handler.updateProductQuality();
			pauseScreen();
			break;
		case 5:
			clearScreen();
			handler.removeProduct();
			pauseScreen();
			break;
		case 6:
			std::cout << "Exiting program." << std::endl;
			return;
		default:
			std::cout << "Invalid option! Please try again!" << std::endl;
			break;
		}
	}
}

int main()
{
	run();
	return 0;
}
