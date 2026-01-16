#pragma once
#include "Product.h"       
#include <string>          
#include <unordered_map>   
#include <map>
#include <set>

const std::string FILE_NAME = "Stock.csv";
const char SEPARATOR = ';';
const char LOCATION_SEPARATOR = ',';

class ProductHandler
{
private:
    size_t nextId = 1;
    std::unordered_map<std::string, Product> products;
    std::set<std::string> occupiedLocation;

    bool isNameValid(const std::string& input) const; 
    std::string locationToString(const Location& loc) const;
    void removeQuality();
    void addQuantity();

public:
    ProductHandler() {}
    ProductHandler(const std::string& db_filename);

    void loadFromFile(const std::string& filename);
    void addProduct();         
    void findProduct() const;    
    void updateProductQuality(); 
    void viewAllProducts() const;
    void saveToFile() const;    
    void removeProduct();
};
