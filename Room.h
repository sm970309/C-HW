#pragma once
#include <iostream>
#include <fstream>
using namespace std;
enum class State{EMPTY,OCCUPIED,PREPARING};
enum class RoomType {STANDARD,SUITE,ROYAL};

class Room
{
	string name;
	int roomNumber;
	int remainTime = 0;
protected:
	double fee;
	int people = 0;
	int addFeePerPerson;
	int breakfastNo = 0;
	static const int breakfastFee = 30;
	double serviceCost = 0;
	State state = State::EMPTY;
public:
	Room() {};
	explicit Room(int rn);
	virtual ~Room() {};
	virtual double calculate() const = 0;
	void checkin(string n, int p, int b = 0);
	void checkout();
	void roomService(int rs);
	void prepare();

	int getRN() { return this->roomNumber; }

	void setroomNumber(int n) { this-> roomNumber = n; }

	string getState() {
		if (state == State::EMPTY) return "EMPTY";
		else if (state == State::OCCUPIED) return "OCCUPIED";
		else if (state == State::PREPARING) return "PREPARING";
	}
	friend ofstream& operator <<(ofstream& stream, const Room& r);

};


