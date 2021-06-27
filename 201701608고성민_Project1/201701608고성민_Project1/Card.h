#pragma once
#include<iostream>
using namespace std;

class Card
{
	char color = ' ';
	int number = 0;
public:
	Card();
	Card(int);
	const int front();
	const char back();
};

