#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Product
{
	string name;
	int price;
	int stock;

public:
	Product() {};
	Product(string n, int p, int s=100);
	friend istream& operator >>(istream& ins, Product& p);
	friend ostream& operator <<(ostream& stream, const Product& p);
	
	//getter 함수
	string getName() { return name; }
	int getStock() { return stock; }
	int getPrice() { return price; }
	//setter 함수
	void setStock(int s) { stock -= s; }		//장바구니에 담을 때, 담는 만큼 재고를 줄이는데 사용
};


