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
	setting >> time >> size;				//ó���� �� �ΰ��� ���Ϸκ��� �Է¹޾� ���� time�� size�� ����

	roomTypes = new RoomType[size];			//size��ŭ roomTypes �� rooms ��ü ����
	rooms = new Room* [size];

	

	for (int i = 0; i < size; i++) {		//size��ŭ �ݺ�
		string rt;							//rt�� roomType
		int rn;								//rn�� roomNumber
		setting >> rt >> rn;				//���������� �� ���� ���Ϸκ��� �Է¹޾� rt,rn�� ����

		if (rt == "s")			//roomType�� s �̸�
		{
			roomTypes[i] = RoomType::STANDARD;		//Standard room���� ����
			rooms[i] = new Standard(rn);			//roomNumber�� Standard ��ü ����
		}
		else if (rt == "u")		//roomType�� u �̸�
		{
			roomTypes[i] = RoomType::SUITE;			//Suite room���� ����
			rooms[i] = new Suite(rn);				//roomNumber�� Suite ��ü ����
		}
		else if (rt == "r")		//roomType�� r �̸�
		{	
			roomTypes[i] = RoomType::ROYAL;			//Royal room���� ����
			rooms[i] = new Royal(rn);				//roomNumber�� Royal ��ü ����
		}
	}
}

void Hotel::open(ifstream& fin) {

	ofstream fout("log.txt");			//log.txt�� �̸��� ���Ϸ� ���

	bool x = true;						//x��� ������ boolŸ������ �����Ͽ��� -> while���� ���

	bool noRoom;						//checkin ������ ���� ���� �� ����ó���� �ϱ� ���� ������ ����
	string name;						
	char op, rt;						// op -> �Է¹޴� ���� ���� �ٸ� ��� ����, rt -> roomType
	int rn,rs, people, breakfast;		// rn -> roomNumber, rs -> roomState, breakfast -> ���� �ο�

	fout << "Time: " << time << ":00\n" << "Hotel opened." << "\n";

	while (x) {							//x�� �ʱⰪ�� true�̹Ƿ� ���� ���� ����
		fin >> op;						//���Ϸκ��� �Է¹��� ���� op�� ����
		
		switch (op)
		{
		case 'a':				//op = a -> �ð� 1�ð� ����
			time += 1;
			if (time >= 24) time = 0;	// time�� 0~23���� ���;� �ϹǷ�, time�� 24�� �Ǹ� 0���� �� ����
			fout << "\nTime: ";
			fout.fill('0');
			fout.width(2);
			fout << time << ":00\n";
			for (int i = 0; i < size; i++) {			//�ð��� ����Կ� ���� remainTime�� 1�� �۾����� �Ѵ�.
				if (rooms[i]->getState() == "PREPARING")		//room�� state�� PREPARING �̸�
					rooms[i]->prepare();						//prepare() �Լ� ȣ��
			}
			break;
		case 'p':				//op = p -> ��� room�� ���� ���
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getState() == "OCCUPIED")		//room�� state�� OCCUPIED�� �ڿ� calculate()���� ���
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
		case 'i':				//op = i -> üũ�� ����
			fin >> rt >> name >> people >> breakfast;
			noRoom = true;		//noRoom�� true�� ���� -> ����ó�� ����
			switch (rt)
			{
			case 's':			//op = s -> Standard Room���� checkin
				for (int i = 0; i < size; i++) {		//0������� size-1������� �˻�
					if (roomTypes[i] == RoomType::STANDARD && rooms[i]->getState() == "EMPTY") //roomType == Standard �̰� state == EMPTY�̸�
					{
						rooms[i]->checkin(name, people, breakfast);			//checkin �Լ� ȣ��
						fout << "Checked in to Standard ";
						fout << *rooms[i] << endl;
						noRoom = false;
						break;
					}
				}
				
				break;

			case 'u':			//op = u -> Suite Room���� checkin
				for (int i = 0; i < size; i++) {
					if (roomTypes[i] == RoomType::SUITE && rooms[i]->getState() == "EMPTY") //roomType == Suite �̰� state == EMPTY�̸�
					{
						rooms[i]->checkin(name, people, breakfast);
						fout << "Checked in to Suite ";
						fout << *rooms[i] << endl;
						noRoom = false;
						break;
					}
				}
				
				break;

			case 'r':			//op = r -> Royal Room���� checkin
				for (int i = 0; i < size; i++) {
					if (roomTypes[i] == RoomType::ROYAL && rooms[i]->getState() == "EMPTY") //roomType == Royal �̰� state == EMPTY�̸�
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
			if (noRoom)		//checkin�� �����ϸ� noRoom�� false�� �ǹǷ� ���� ������ ������� �ʴ´�.
				fout << "Fail to check in\nNo Empty Room for " << name << endl;			//true�϶� ����ó��
			break;
		case 'o':		//op = o -> üũ�ƿ� ����
			fin >> rn;
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getRN() == rn)		//room�� roomNumber�� �Է¹��� rn�� ������ ���� -> �Է¹��� roomNumber�� ã�� üũ�ƿ�
				{
					fout << roomTypes[i];
					fout << *rooms[i] << " checked out.\n";
					fout << "$" << rooms[i]->calculate() << " added to the total income\n";
					totalIncome +=  rooms[i]->calculate();
					rooms[i]->checkout();			//checkout()�Լ� ȣ��
					break;
				}
			}
			break;
		case 's':
			fin >> rn >> rs;
			
			for (int i = 0; i < size; i++) {
				if (rooms[i]->getRN() == rn)		//room�� roomNumber�� �Է¹��� rn�� ������ ���� -> �Է¹��� roomNumber�� ã�� �뼭�� ����
				{
					fout << roomTypes[i];
					fout<< *rooms[i] <<" called room service($" <<rs <<")"<<endl;
					rooms[i]->roomService(rs);		//roomService() ȣ��
					break;
				}
				
			}
			break;
		case'q':
			fout << "\nHotel closed.\nTotal income is $" << totalIncome;
			x = false;		//x�� false�� �����ϸ� while�� �۵� x -> ���� ���� Ż��
			break;
		}
		

	}
}

