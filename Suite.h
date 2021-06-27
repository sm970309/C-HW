#pragma once
#include "Room.h"
class Suite :
    public Room
{
public:
    Suite(int rn);
    double calculate() const;
};

