#include "Game.h"

const void Game::advanceRound() {
	int n;								// user의 턴에 입력받는 값

	Card Computer, User;				//computer와 user가 선택한 카드를 받는 객체 생성
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

	if (comp_first) {															//comp_first가 true면 computer 먼저
		cout << "\ncomputer's turn" << "\n\n";
		Computer =  computer->choose(rand()%(computer->getNum_card()+1));		//0부터 num_card(최초값은 8) 까지의 랜덤한 index를 choose -> 이후 num_card-1 (choose에서 실행)
		cout << "computer chose : " << Computer.back()<<"\n\n\n";				//computer는 '값'을 랜덤으로 뽑나 'index'를 랜덤으로 뽑나 별 차이가 없을거 같아서 이렇게 구현
		cout << "Your turn!" << endl;
		while (true) {
			cout << "Which Card will you choose? ";								//올바른 값이 들어올 때 까지 무한루프
			cin >> n;						
			if (user->search(n) == -1) {										//search에서 n이 deck에 없으면 -1을 리턴
				cout << "No " << n << " in deck!" << endl;						//루프
			}
			else break;															//n이 deck에 있으면 무한루프 탈출
		}
		User = user->choose(user->search(n));
		cout << "\nuser chose : " << User.front() << "\n";
	}
	else {																		//comp_first가 false면 user먼저
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