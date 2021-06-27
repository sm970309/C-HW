#include "Hotel.h"

ofstream& operator <<(ofstream& log, const RoomType& rt) {
	if (rt == RoomType::STANDARD)
		log << "Standard ";
	else if (rt == RoomType::SUITE)
		log << "Suite ";
	else if (rt == RoomType::ROYAL)
		log << "Royal ";
	return log;
}

ofstream& operator <<(ofstream& fout, const Room& r) {
	if (r.state == State::EMPTY)
		fout << "Room " << r.roomNumber << " Empty";
	else if (r.state == State::OCCUPIED)
		if (r.people == 1)
			fout << "Room " << r.roomNumber << " Occupied(" << r.name << ")";
		else
			fout << "Room " << r.roomNumber << " Occupied(" << r.name << " and " << r.people - 1 << " others)";
	else if (r.state == State::PREPARING)
		fout << "Room " << r.roomNumber << " Preparing(" << r.remainTime << " hours left) ";
	return fout;
}

Hotel::Hotel(ifstream& setting) {
	setting >> time >> size;				//처음에 값 두개를 파일로부터 입력받아 각각 time과 size에 대입

	roomTypes = new RoomType[size];			//size만큼 roomTypes 과 rooms 객체 생성
	rooms = new Room* [size];

	

	for (int i = 0; i < size; i++) {		//size만큼 반복
		string rt;							//rt는 roomType
		int rn;								//rn은 roomNumber
		setting >> rt >> rn;				//마찬가지로 두 값을 파일로부터 입력받아 rt,rn에 대입

		if (rt == "s")			//roomType이 s 이면
		{
			roomTypes[i] = RoomType::STANDARD;		//Standard room으로 설정
			rooms[i] = new Standard(rn);			//roomNumber로 Standard 객체 생성
		}
		else if (rt == "u")		//roomType이 u 이면
		{
			roomTypes[i] = RoomType::SUITE;			//Suite room으로 설정
			rooms[i] = new Suite(rn);				//roomNumber로 Suite 객체 생성
		}
		else if (rt == "r")		//roomType이 r 이면
		{	
			roomTypes[i] = RoomType::ROYAL;			//Royal room으로 설정
			rooms[i] = new Royal(rn);				//roomNumber로 Royal 객체 생성
		}
	}
}

void Hotel::open(ifstream& fin) {

	ofstream fout("log.txt");			//log.txt라른 이름의 파일로 출력

	bool x = true;						//x라는 변수를 bool타입으로 정의하였다 -> while문에 사용

	bool noRoom;						//checkin 가능한 방이 없을 때 예외처리를 하기 위해 선언한 변수
	string name;						
	char op, rt;						// op -> 입력받는 값에 따라 다른 명령 실행, rt -> roomType
	int rn,rs, people, breakfast;		// rn -> roomNumber, rs -> roomState, breakfast -> 조식 인원

	fout << "Time: " << time << ":00\n" << "Hotel opened." << "\n";

	while (x) {							//x의 초기값이 true이므로 무한 루프 생성
		fin >> op;						//파일로부터 입력받은 값을 op에 대입
		
		switch (op)
		{
		case 'a':				//op = a -> 시간 1시간 증가
			time += 1;
			if (time >= 24) time = 0;	// time은 0~23까지 나와야 하므로, time이 24가 되면 0으로 값 변경
			fout << "\nTime: ";
			fout.fill('0');
			fout.width(2);
			fout << time << ":00\n";
			for (int i = 0; i < size; i++) {			//시간이 경과함에 따라 remainTime이 1씩 작아져야 한다.
				if (rooms[i]->getState() == "PREPARING")		//room의 state가 PREPARING 이면
					rooms[i]->prepare();						//prepare() 함수 호출
			}
			break;
		case 'p':				//op = p -> 모든 room의 정보 출력
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getState() == "OCCUPIED")		//room의 state가 OCCUPIED면 뒤에 calculate()값을 출력
				{
					
					fout << roomTypes[i];
					fout << *rooms[i] << " $" << rooms[i]->calculate() << " expected" <<endl;
					
				}
				else 
				{
					fout << roomTypes[i];
					fout << *rooms[i] << endl;
				
				}
			}
			break;
		case 'i':				//op = i -> 체크인 실행
			fin >> rt >> name >> people >> breakfast;
			noRoom = true;		//noRoom을 true로 설정 -> 예외처리 구현
			switch (rt)
			{
			case 's':			//op = s -> Standard Room으로 checkin
				for (int i = 0; i < size; i++) {		//0번방부터 size-1번방까지 검색
					if (roomTypes[i] == RoomType::STANDARD && rooms[i]->getState() == "EMPTY") //roomType == Standard 이고 state == EMPTY이면
					{
						rooms[i]->checkin(name, people, breakfast);			//checkin 함수 호출
						fout << "Checked in to Standard ";
						fout << *rooms[i] << endl;
						noRoom = false;
						break;
					}
				}
				
				break;

			case 'u':			//op = u -> Suite Room으로 checkin
				for (int i = 0; i < size; i++) {
					if (roomTypes[i] == RoomType::SUITE && rooms[i]->getState() == "EMPTY") //roomType == Suite 이고 state == EMPTY이면
					{
						rooms[i]->checkin(name, people, breakfast);
						fout << "Checked in to Suite ";
						fout << *rooms[i] << endl;
						noRoom = false;
						break;
					}
				}
				
				break;

			case 'r':			//op = r -> Royal Room으로 checkin
				for (int i = 0; i < size; i++) {
					if (roomTypes[i] == RoomType::ROYAL && rooms[i]->getState() == "EMPTY") //roomType == Royal 이고 state == EMPTY이면
					{
						rooms[i]->checkin(name, people, breakfast);
						fout << "Checked in to Royal ";
						fout << *rooms[i] << endl;
						noRoom = false;
						break;
					}
				}				
				break;
			
			}
			if (noRoom)		//checkin에 성공하면 noRoom은 false가 되므로 다음 문장이 실행되지 않는다.
				fout << "Fail to check in\nNo Empty Room for " << name << endl;			//true일때 예외처리
			break;
		case 'o':		//op = o -> 체크아웃 실행
			fin >> rn;
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getRN() == rn)		//room의 roomNumber가 입력받은 rn과 같으면 실행 -> 입력받은 roomNumber를 찾아 체크아웃
				{
					fout << roomTypes[i];
					fout << *rooms[i] << " checked out.\n";
					fout << "$" << rooms[i]->calculate() << " added to the total income\n";
					totalIncome +=  rooms[i]->calculate();
					rooms[i]->checkout();			//checkout()함수 호출
					break;
				}
			}
			break;
		case 's':
			fin >> rn >> rs;
			
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getRN() == rn)		//room의 roomNumber가 입력받은 rn과 같으면 실행 -> 입력받은 roomNumber를 찾아 룸서비스 실행
				{
					fout << roomTypes[i];
					fout<< *rooms[i] <<" called room service($" <<rs <<")"<<endl;
					rooms[i]->roomService(rs);		//roomService() 호출
					break;
				}
				
			}
			break;
		case'q':
			fout << "\nHotel closed.\nTotal income is $" << totalIncome;
			x = false;		//x를 false로 변경하면 while문 작동 x -> 무한 루프 탈출
			break;
		}
		

	}
}

