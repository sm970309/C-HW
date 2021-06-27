#pragma once
#include "Room.h"
class Standard :
    public Room
{
public:
    Standard(int rn);
    double calculate() const;
    
};

