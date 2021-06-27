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
	
	//getter �Լ�
	string getName() { return name; }
	int getStock() { return stock; }
	int getPrice() { return price; }
	//setter �Լ�
	void setStock(int s) { stock -= s; }		//��ٱ��Ͽ� ���� ��, ��� ��ŭ ��� ���̴µ� ���
};


