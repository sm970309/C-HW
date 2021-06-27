#pragma once
#include "Product.h"
#include <vector>
#include<string>

class ShoppingManager
{
	vector<Product> productList;

public:
	ShoppingManager(const string fn);

	vector<Product> cartList;

	void mainMenu();
	void managerMode();
	void customerMode();
	void cartMode();

	void addProduct();
	void deleteProduct();
	void print(vector<Product> pList);
	void search();
	
	void addToCart();
	void calculate();
};
