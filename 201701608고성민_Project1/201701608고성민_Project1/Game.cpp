#include "Game.h"

const void Game::advanceRound() {
	int n;								// user�� �Ͽ� �Է¹޴� ��

	Card Computer, User;				//computer�� user�� ������ ī�带 �޴� ��ü ����
	cout << "================================" << endl << "Round : " << round << endl << "================================" << endl;
	cout << "<computer cards>" << endl;
	for (int i = 0; i < computer->getNum_card()+1; i++) {
		cout << " _ ";
	}
	cout << endl;
	computer->printBack();
	cout << endl;
	for (int i = 0; i < computer->getNum_card()+1; i++) {
		cout << " - ";
	}
	cout << endl;
	cout << "<user cards>" << endl;
	for (int i = 0; i < computer->getNum_card() + 1; i++) {
		cout << " _ ";
	}
	cout << endl;
	user->printFront();
	cout << endl;
	for (int i = 0; i < computer->getNum_card() + 1; i++) {
		cout << " - ";
	}

	if (comp_first) {															//comp_first�� true�� computer ����
		cout << "\ncomputer's turn" << "\n\n";
		Computer =  computer->choose(rand()%(computer->getNum_card()+1));		//0���� num_card(���ʰ��� 8) ������ ������ index�� choose -> ���� num_card-1 (choose���� ����)
		cout << "computer chose : " << Computer.back()<<"\n\n\n";				//computer�� '��'�� �������� �̳� 'index'�� �������� �̳� �� ���̰� ������ ���Ƽ� �̷��� ����
		cout << "Your turn!" << endl;
		while (true) {
			cout << "Which Card will you choose? ";								//�ùٸ� ���� ���� �� ���� ���ѷ���
			cin >> n;						
			if (user->search(n) == -1) {										//search���� n�� deck�� ������ -1�� ����
				cout << "No " << n << " in deck!" << endl;						//����
			}
			else break;															//n�� deck�� ������ ���ѷ��� Ż��
		}
		User = user->choose(user->search(n));
		cout << "\nuser chose : " << User.front() << "\n";
	}
	else {																		//comp_first�� false�� user����
		cout << "\nYour turn!" << endl << "\nWhich Card will you choose? ";
		while (true) {
			cout << "Which Card will you choose? ";
			cin >> n;
			if (user->search(n) == -1) {
				cout << "No " << n << " in deck!" << endl;
			}
			else break;
		}
		User = user->choose((user->search(n)));
		cout << "\nuser chose : " << User.front() << "\n";
		cout << "computer's turn" << "\n\n";

		Computer = computer->choose(rand() % (computer->getNum_card()+1));
		cout << "computer chose : " << Computer.back() << "\n\n\n";
	}

	if (User.front() > Computer.front()) {
		cout << ">>>>> user won!"<<endl;
		comp_first = false;							
		user_wins++;
	}
	else if (User.front() == Computer.front()) {
		cout << ">>>>> draw"<<endl;
	}
	else {
		cout << ">>>>> computer won!"<<endl;
		comp_first = true;
		comp_wins++;

	}
	round++;
}


const void Game::play() {
	computer = new Player[9];
	user = new Player[9];

	computer->randomShuffle();
	for (int i = 0; i <9; i++) {
		
		advanceRound();
		cout << endl;
	}
	cout << "===============================" << endl;
	cout << "All rounds have ended" << endl;
	cout << "===============================" << endl;
	cout << "user won " << user_wins << " times" << endl;
	cout << "computer won " << comp_wins << " times" << endl;

	if (user_wins>comp_wins) cout << "Congratulations! You Won!!! :)\n\n";
	else if (user_wins == comp_wins) cout << ">>>>> Draw\n\n";
	else cout << "You lose :(\n\n";

	cout << "user history      : ";
	user->printHistory();
	cout << endl;
	cout << "computer history  : ";
	computer->printHistory();
	cout << endl;
	
}