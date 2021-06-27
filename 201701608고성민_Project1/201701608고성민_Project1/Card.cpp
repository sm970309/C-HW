#include "Card.h"

Card::Card() {};
Card::Card(int n) {
	this->number = n;
	if (number % 2 != 0) this->color = 'w';			//입력받은 n이 홀수이면 'w', 짝수이면 'b'로 받아서 객체 생성
	else this->color = 'b';
}
const int Card::front() { return number; }
const char Card::back() { return color; }
