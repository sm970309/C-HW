#pragma once
#include "Room.h"
class Royal :
    public Room
{
public:
    Royal(int rn);
    double calculate() const;
    void roomService(int rs);
};

