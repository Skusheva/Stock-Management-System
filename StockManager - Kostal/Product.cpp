#include "Product.h"
#include <iostream>

Product::Product() : product_Id(0), articleNumber(""), name(""), quality(0), location() { }

Product::Product(size_t id, std::string& articleNumber, std::string& name, size_t quality, Location location) :
	product_Id(id), articleNumber(articleNumber), name(name), quality(quality), location(location) { }

Product::Product( std::string& articleNumber, std::string& name)
	: articleNumber(articleNumber), name(name), quality(0), location() { }

size_t Product::getProduct_Id() const {
	return product_Id;
}

std::string Product::getArticleNumber() const {
	return articleNumber;
}

std::string Product::getName() const {
	return name;
}

size_t Product::getQuality() const {
	return quality;
}

Location Product::getLocation() const {
	return location;
}

void Product::setProduct_id(size_t newProduct_Id) {
	product_Id = newProduct_Id;
}

void Product::setQuality(size_t newQuality) {
	quality = newQuality;
}

bool Product::addQuality(size_t amount) {
	quality += amount;
	return true;
}

bool Product::removeQuality(size_t amount) {
		if (amount > quality) {
			std::cout << "Insufficient availability!" << std::endl;
			std::cout << "There is not enough available quantity to perform the operation.Please enter amount less than available." << std::endl;
			return false;
		}
		quality -= amount;
		return true;
}

void Product::setLocation(const Location& loc) {
	location = loc;
}

void Product::print() const {
	std::cout << "ArticleNumber: " << articleNumber << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Quality: " << quality << std::endl;
	std::cout << "Location: " << location.x << " , " << location.y << std::endl;
}

Product& Product::operator=(const Product& other) {
	if (this != &other) {
		product_Id = other.product_Id;
		articleNumber = other.articleNumber;
		name = other.name;
		quality = other.quality;
		location = other.location;
	}
	return *this;
}