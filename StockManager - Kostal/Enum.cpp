#include "Enum.h"
#include <iostream>

size_t getValidCoordinate() {

    double numericValue;

    while (true) {
        std::cin >> numericValue;

        if (std::cin.fail()) {
            std::cout << "Error! You must enter a number! Please try again!" << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue;
        }
        if (numericValue <= 0) {
            std::cout << "Error! You must enter a positive number! Please try again." << std::endl;
            continue;
        }

        long long roundedValue = round(numericValue);
        if (numericValue != static_cast<double>(roundedValue)) {
            std::cout << "Information: The entered value: " << numericValue << "is not an integer!It was rounded to: " << roundedValue << std::endl;
        }

        return static_cast<size_t>(roundedValue);
    }
}

Location inputLocation() {
    Location loc;
    std::cout << "Please enter a value for the row! Enter a positive number: ";
    loc.x = getValidCoordinate();
    std::cout << "Please enter a value for the position! Enter a positive number: ";
    loc.y = getValidCoordinate();
    return loc;
}


