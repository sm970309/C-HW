#pragma once
#include "Room.h"
#include "Standard.h"
#include "Suite.h"
#include "Royal.h"

class Hotel
{
	Room** rooms;
	int time;
	int size;
	int totalIncome = 0;
	RoomType* roomTypes;

public:
	Hotel(ifstream& setting);
	void open(ifstream& fin);

};

