#include "Player.h"

Player::Player() {
	deck = new Card[9];
	for (int i = 0; i < 9; i++) {
		deck[i] = Card(i);
	}
}
Card Player::choose(int n) {
	Card tmp = deck[n];						//�ӽ� ��ü�� ����
	history[cnt] = deck[n].front();			//��� ���� cnt(�ʱⰪ 0)�� Ȱ���Ͽ� deck�� n��° index�� number���� history�� cnt��° index�� ������� 
	cnt++;									//���� index�� ���� �����ϱ� ���� choose�� ������ �� ���� cnt++

	for (n; n < num_card; n++) {			//���� index ���� ������ ��ĭ�� ������ ���
		deck[n] = deck[n + 1];
	}
	num_card--;								//���ӿ� ����ϴ� ���� ī�� 8���� ���徿 ����  				
	return tmp;
}

int Player::search(int n) {
	for (int i = 0; i < num_card + 1; i++) {			
		if (deck[i].front() == n) {					//n ���� �޾� deck�� i��° index�� ������ index�� ����

			return i;
			break;
		}
	}
	return -1;										//for���� �߰��� Ż������ ���ϸ�(=deck�� n�� ������) -1�� ���� 
}													//���߿� ����ó���� ���ؼ� ����
const void Player::printBack() {
	for (int i = 0; i < num_card + 1; i++) {
		cout << "|" << (deck + i)->back() << "|";
	}
}
const void Player::printFront() {
	for (int i = 0; i < num_card + 1; i++) {
		cout << "|" << (deck + i)->front() << "|";
	}
}
const void Player::printHistory() {
	for (int i = 0; i<9; i++) {
		cout << history[i]<<" ";
	}
}
void Player::randomShuffle() {
	Card tmp; 
	int rn; 
	for (int i = 0; i < 9; i++) {
		rn = rand() % (9-i);
		tmp = deck[i];
		deck[i] = deck[rn];
		deck[rn] = tmp;
	}
}
Player::~Player() {
	delete [] deck;
}
const int Player::getNum_card() { return num_card; }		//num_card�� �ٸ� Ŭ�������� ����ϱ� ���� ����