#include "ProductHandler.h"
#include "Enum.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool ProductHandler::isNameValid(const std::string& name) const  {

    if (name.empty()) {
        std::cout << "Error! Name can not be empty!" << std::endl;
        return false;
    }

    bool foundNonSpace = false;
    for (char c : name) {
        if (!std::isspace(c)) {
            foundNonSpace = true;
            break;
        }
    }
    if (!foundNonSpace) {
        std::cout << "Error! Name can not be just from spaces!" << std::endl;
        return false;
    }

    for (char c : name) {
        if (c == SEPARATOR || c == LOCATION_SEPARATOR || c == '"') {
            std::cout << "Error! Symbols: " << SEPARATOR << "' , '" << LOCATION_SEPARATOR << "' and '\"' are not allowed! Please do not enter them!" << std::endl;
            return false;
        }
    }
	return true;
}

std::string ProductHandler::locationToString(const Location& loc) const {
    return std::to_string(loc.x) + LOCATION_SEPARATOR + std::to_string(loc.y);
}

ProductHandler::ProductHandler(const std::string& db_filename) : nextId(1) {
    loadFromFile(db_filename);
}

void ProductHandler::removeQuality() {
        std::cout << " === Remove Quantity === " << std::endl;
        std::cout << "Please enter Article Number of the product to update: ";
        std::string articleNumber;
        getline(std::cin, articleNumber);

        if (products.count(articleNumber)) {
            Product& productToUpdate = products.at(articleNumber);
            std::cout << "Current quality for '" << productToUpdate.getName() << "' is " << productToUpdate.getQuality() << std::endl;

            while (true) {
                std::cout << "Please enter how much you want to remove: ";
                size_t amount;
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (productToUpdate.removeQuality(amount)) {
                    std::cout << "Successfully removed. New quality: " << productToUpdate.getQuality() << std::endl;
                    saveToFile();
                    break;
                }
            }
        }
        else {
            std::cout << "Error: Product with this Article Number not found." << std::endl;
        }
}

void ProductHandler::addQuantity() {
    std::cout << " === Add Quantity === " << std::endl;
    std::cout << "Please enter Article Number of the product to update: ";
    std::string articleNumber;
    getline(std::cin, articleNumber);

    if (products.count(articleNumber)) {
        Product& productToUpdate = products.at(articleNumber);
        std::cout << "Current quality for '" << productToUpdate.getName() << "' is " << productToUpdate.getQuality() << std::endl;

        std::cout << "Please enter how much you want to add: ";
        size_t amount;
        std::cin >> amount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (productToUpdate.addQuality(amount)) {
            std::cout << "Successfully added. New quality: " << productToUpdate.getQuality() << std::endl;
            saveToFile();
        }
    }
    else {
        std::cout << "Error: Product with this Article Number not found." << std::endl;
    }
}

void ProductHandler::loadFromFile(const std::string& filename) {

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "No information " << filename << " File its not found ." << std::endl;
        return;
    }

    std::string line;
    getline(inFile, line);

    size_t maxId = 0;

    while (getline(inFile, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string idStr, articleNumber, name, qualityStr, locationStr;

        if (!std::getline(ss, idStr, SEPARATOR))
            continue;
        if (!std::getline(ss, articleNumber, SEPARATOR))
            continue;
        if (!std::getline(ss, name, SEPARATOR))
            continue;
        if (!std::getline(ss, qualityStr, SEPARATOR))
            continue;
        if (!std::getline(ss, locationStr))
            continue;

        size_t Id = std::stoi(idStr);
        size_t quality = std::stoi(qualityStr);

        size_t pos = locationStr.find(LOCATION_SEPARATOR);
        size_t x = std::stoi(locationStr.substr(0, pos));
        size_t y = std::stoi(locationStr.substr(pos + 1));

        Location loc = { x,y };

        Product loadedProduct(articleNumber, name);
        loadedProduct.setProduct_id(Id);
        loadedProduct.setQuality(quality);
        loadedProduct.setLocation(loc);
        
        products[articleNumber] = loadedProduct;
        occupiedLocation.insert(locationToString(loc));

        if (Id > maxId)
            maxId = Id;
    }

    nextId = maxId + 1;

    inFile.close();
}

void ProductHandler::addProduct() {
	
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string articleNumber, name;
	int quality;
	Location loc;
    bool active = 1;
	std::cout << "=== Add Product ===" << std::endl;
	std::cout << "Please enter articleNumber: ";
    getline(std::cin, articleNumber);
    if (products.count(articleNumber)) {
        std::cout << "Error: A product with this article number already exists!" << std::endl;
        return;
    }
		
    while (true) {
        std::cout << "Please enter a name:";;
        getline(std::cin, name);
        if (!isNameValid(name)) {
            std::cout << "Please enter upper, lower letters , numbers or symbols!" << std::endl;
        }
        else
            break;
    }

    while (true) {
        std::cout << "Please enter quality: ";
        std::cin >> quality;
        if (quality < 0)
            std::cout << "Error! This is invalid input! Please enter a number!!!" << std::endl;
        else
            break;
    }

    while (true) {
        std::cout << "Please enter location: " << std::endl;
        loc = inputLocation();

        std::string locStr = locationToString(loc);
        if (occupiedLocation.count(locStr))
            std::cout << "This location is already taken! Please enter another location!" << std::endl;
        else
            break;
    }
    
	Product newProduct(articleNumber,name);
    newProduct.setProduct_id(nextId++);
	newProduct.setLocation(loc);
	newProduct.setQuality(quality);
	products[newProduct.getArticleNumber()] = newProduct;

    occupiedLocation.insert(locationToString(loc));
	
    saveToFile();
    std::cout << "Congratulations!!! You have successfully added the product!" << std::endl;
}

void ProductHandler::saveToFile() const {
    std::ofstream outFile(FILE_NAME);
    if (!outFile.is_open()) {
        std::cout<<"Error! File is not open correctly! " << std::endl;
        return;
    }

    outFile << "ID" << SEPARATOR
        << "ArticleNumber" << SEPARATOR
        << "Name" << SEPARATOR
        << "Quality" << SEPARATOR
        << "Location" << std::endl;

    for (const auto& pair : products) {
        const Product& p = pair.second;
        const Location& l = p.getLocation();

        std::string LocationStr = std::to_string(l.x) + LOCATION_SEPARATOR + std::to_string(l.y);

        outFile << p.getProduct_Id() << SEPARATOR
            << p.getArticleNumber() << SEPARATOR
            << p.getName() << SEPARATOR
            << p.getQuality() << SEPARATOR
            << LocationStr << std::endl;
    }

    outFile.close();
}

void ProductHandler::findProduct() const {
    while (true) {
        std::cout << " === Search for a Product ===" << std::endl;
        std::cout << " Please choose option - 1 or 2 - how you want to search a product! " << std::endl;
        std::cout << " 1. Search by Article Number " << std::endl;
        std::cout << " 2. Search by Name" << std::endl;
        std::cout << " 3. Cancel " << std::endl;
        std::cout << "Please make your choice: ";
        double tempChoice;
        std::cin >> tempChoice;

        if(std::cin.fail()) {
            std::cout << "Error! You have to enter a number - 1,2 or 3!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (tempChoice != static_cast<int>(tempChoice)){
            std::cout << "Error! Please enter whole number!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        int choice = static_cast<int>(tempChoice);
        if (choice != 1 && choice != 2 && choice != 3) {
            std::cout << "You have to choose between numbers 1,2 or 3! Please try again! " << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Enter Article Number: ";
            std::string articleNumber;
            getline(std::cin, articleNumber);
            auto it = products.find(articleNumber);
            if (it != products.end()) {
                std::cout << "Congratulations!!!Product found:" << std::endl;
                std::cout << "--------------------------" << std::endl;
                it->second.print();
                std::cout << "--------------------------" << std::endl;

                if (it->second.getQuality() == 0) {
                    std::cout << "This product is not available in this moment! Expect a charge soon!" << std::endl;
                    std::cout << "--------------------------" << std::endl;
                }
            }
            else {
                std::cout << "No product found with this Article Number! Please try again with another Article Number!" << std::endl;
            }
        }
        else if (choice == 2) {
            std::cout << "Enter text to search in name: ";
            std::string searchTerm;
            getline(std::cin, searchTerm);

            bool found = false;
            for (const auto& pair : products) {
                if (pair.second.getName().find(searchTerm) != std::string::npos) {
                           std::cout << "Congratulations!!!Found matching products: " << std::endl;
                           std::cout << "--------------------------" << std::endl;
                    pair.second.print();
                    std::cout << "--------------------------" << std::endl;

                    if (pair.second.getQuality() == 0) {
                        std::cout << "This product is not available in this moment! Expect a charge soon!" << std::endl;
                        std::cout << "--------------------------" << std::endl;
                    }
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No products found with a name containing: '" << searchTerm << "'." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "Cancelled." << std::endl;
            break;
        }
    }
}

void ProductHandler::viewAllProducts() const {
    if (products.empty()) {
        std::cout << std::endl;
        std::cout << "The stock is empty." << std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout << " === All Products in Stock === " << std::endl;
    for (const auto& pair : products) {
        pair.second.print();
        std::cout << "--------------------------" << std::endl;
        if (pair.second.getQuality() == 0) {
            std::cout << "This product is not available in this moment! Expect a charge soon!" << std::endl;
            std::cout << "--------------------------" << std::endl;
        }
    }
}

void ProductHandler::updateProductQuality() {
    while (true) {
        std::cout << " === Quantity update === " << std::endl;
        std::cout << " Please choose option - 1 or 2 - what do you want to do: " << std::endl;
        std::cout << " 1. Remove Quantity " << std::endl;
        std::cout << " 2. Add Quantity " << std::endl;
        std::cout << " 3. Cancel " << std::endl;
        std::cout << "Please make your choice: ";
        double tempChoice;
        std::cin >> tempChoice;

        if (std::cin.fail()) {
            std::cout << "Error! You have to enter a number - 1 or 2!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (tempChoice != static_cast<int>(tempChoice)) {
            std::cout << "Error! Please enter whole number!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        int choice = static_cast<int>(tempChoice);
        if (choice != 1 && choice != 2 && choice != 3) {
            std::cout << "You have to choose between numbers 1 or 2! Please try again! " << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            removeQuality();
        }
        if (choice == 2) {
            addQuantity();
            break;
        }
        if (choice == 3) {
            std::cout << "Cancelled." << std::endl;
            break;
        }
    }
}

void ProductHandler::removeProduct() {
        std::cout << " === Remove Product === " << std::endl;
        while (true) {
        std::cout << "Please enter Article Number of the product to remove: ";
        std::string articleNumber;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, articleNumber);
        if (products.count(articleNumber)) {
            Product& productToDeactivate = products.at(articleNumber);
            occupiedLocation.erase(locationToString(productToDeactivate.getLocation()));
            products.erase(articleNumber);
            std::cout << "Product removed successfully." << std::endl;
            saveToFile();
            break;
        }
        else {
            std::cout << "Error: Product not found.Please try again with different Article Number!" << std::endl;
        }
    }
}