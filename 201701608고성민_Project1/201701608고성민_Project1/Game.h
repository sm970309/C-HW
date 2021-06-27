#pragma once
#include "Player.h"
class Game
{	
	Player* computer;
	Player* user;
	int round=1;
	bool comp_first = true;
	int user_wins=0;
	int comp_wins=0;

public:
	const void play();
	const void advanceRound();

};

