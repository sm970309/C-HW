#include "Card.h"

Card::Card() {};
Card::Card(int n) {
	this->number = n;
	if (number % 2 != 0) this->color = 'w';			//�Է¹��� n�� Ȧ���̸� 'w', ¦���̸� 'b'�� �޾Ƽ� ��ü ����
	else this->color = 'b';
}
const int Card::front() { return number; }
const char Card::back() { return color; }
