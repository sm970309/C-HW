#include "Player.h"

Player::Player() {
	deck = new Card[9];
	for (int i = 0; i < 9; i++) {
		deck[i] = Card(i);
	}
}
Card Player::choose(int n) {
	Card tmp = deck[n];						//임시 객체에 저장
	history[cnt] = deck[n].front();			//멤버 변수 cnt(초기값 0)를 활용하여 deck의 n번째 index의 number값을 history의 cnt번째 index에 집어넣음 
	cnt++;									//다음 index에 값을 대입하기 위해 choose를 실행할 때 마다 cnt++

	for (n; n < num_card; n++) {			//뽑은 index 다음 값부터 한칸씩 앞으로 당김
		deck[n] = deck[n + 1];
	}
	num_card--;								//게임에 사용하는 최초 카드 8장을 한장씩 줄임  				
	return tmp;
}

int Player::search(int n) {
	for (int i = 0; i < num_card + 1; i++) {			
		if (deck[i].front() == n) {					//n 값을 받아 deck의 i번째 index와 같으면 index를 리턴

			return i;
			break;
		}
	}
	return -1;										//for문을 중간에 탈출하지 못하면(=deck에 n이 없으면) -1을 리턴 
}													//나중에 예외처리를 위해서 구현
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
const int Player::getNum_card() { return num_card; }		//num_card를 다른 클래스에서 사용하기 위해 구현