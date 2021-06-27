#include "Room.h"

Room::Room(int rn) {				//���� �ʱ�ȭ
	name = "";
	roomNumber = rn;
	fee = 0; 
	addFeePerPerson = 0;
}

void Room::checkin(string n, int p, int b) {		//checkin -> ���� ����
	name = n;
	people = p;
	breakfastNo = b;
	state = State::OCCUPIED;						//room�� state = OCCUPIED��
}
void Room::checkout() {								//checkout -> ���� ���
	name = "";
	people = 0;
	breakfastNo = 0;
	remainTime = 4;
	state = State::PREPARING;						//room�� state = PREPARING
}

void::Room::roomService(int rs) {
	serviceCost += rs;
}
void Room::prepare() {
	remainTime -= 1;								//remainTime�� 1�� ����
	if (remainTime == 0) state = State::EMPTY;		//remainTime�� 0�̸� �غ� �� -> state =EMPTY
}