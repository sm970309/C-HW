#pragma once
#include "Card.h"
class Player
{
	Card* deck;
	int num_card = 8;
	int cnt = 0;
	int history[9];

public:
	Player();
	~Player();
	void randomShuffle();
	Card choose(int);
	int search(int);
	const void printFront();
	const void printBack();
	const void printHistory();
	const int getNum_card();
};

