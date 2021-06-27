#include "Room.h"

Room::Room(int rn) {				//변수 초기화
	name = "";
	roomNumber = rn;
	fee = 0; 
	addFeePerPerson = 0;
}

void Room::checkin(string n, int p, int b) {		//checkin -> 방이 찬다
	name = n;
	people = p;
	breakfastNo = b;
	state = State::OCCUPIED;						//room의 state = OCCUPIED로
}
void Room::checkout() {								//checkout -> 방이 빈다
	name = "";
	people = 0;
	breakfastNo = 0;
	remainTime = 4;
	state = State::PREPARING;						//room의 state = PREPARING
}

void::Room::roomService(int rs) {
	serviceCost += rs;
}
void Room::prepare() {
	remainTime -= 1;								//remainTime을 1씩 감소
	if (remainTime == 0) state = State::EMPTY;		//remainTime이 0이면 준비 끝 -> state =EMPTY
}