#pragma once
#include <string>
#include "Enum.h"


class Product {

private:
	size_t product_Id;
	std::string articleNumber;
	std::string name;
	size_t quality;
	Location location;

public:
	Product();
	Product(size_t product_Id, std::string& articleNumber, std::string& name, size_t quality, Location location);
	Product(std::string& articleNumber, std::string& name);

	size_t getProduct_Id() const;
	std::string getArticleNumber() const;
	std::string getName() const;
	size_t getQuality() const;
	Location getLocation() const;

	void setProduct_id(size_t new_ProductId);
	void setQuality(size_t newQuality);
	bool addQuality(size_t amount);
	bool removeQuality(size_t amount);
	void setLocation(const Location& loc);

	void print() const;

	Product& operator=(const Product& other);
};

