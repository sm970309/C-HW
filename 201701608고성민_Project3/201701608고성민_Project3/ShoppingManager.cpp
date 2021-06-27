#include "ShoppingManager.h"


ostream& operator <<(ostream& stream, const Product& p) {		//조작자를 사용해서 항목들을 정렬하였다.


	stream << "상품명 : ";
	stream.width(20);
	stream << left << p.name;
	stream << "가격 : ";
	stream.width(10);
	stream << right << p.price << "원 ";
	stream << " 재고/수량 : " << p.stock << "개";
	return stream;
}
istream& operator >>(istream& ins, Product& p) {

	cout << "\n상품 이름 입력 : ";
	ins.ignore();
	getline(ins,p.name);
	if (p.name != "no") {				
		cout << "상품 가격 입력 : ";
		ins >> p.price;
	}
	return ins;
}
ShoppingManager::ShoppingManager(const string fn) {
	ifstream fin;
	fin.open(fn);
	while (fin.eof() == false) {	//파일의 끝까지 반복
		string n;
		getline(fin, n);		//한줄씩 읽어오기

		//substr(index1,index2) -> index1부터 index2까지 저장
		string fisrt = n.substr(0, n.find(";"));		//0번 인덱스부터 ;위치의 인덱스 까지 first에 저장
		int second = stoi(n.substr(n.find(";") + 1));	//;위치 인덱스+1 부터 끝까지 second에 저장
		
		//Product 생성자 만들기
		Product product(fisrt, second);					//first -> 제품명 , second -> 가격 (stoi로 int타입으로 변경)
		productList.push_back(product);					//vector에 push_back
	}
	fin.close();
}

void ShoppingManager::mainMenu() {
	
	while (true) {
		int op, passwd;
		cout << "<< INU 쇼핑에 오신 것을 환영합니다! >>" << endl;
		cout << "[1] 쇼핑 관리자 모드\n[2] 고객모드\n[3] 종료\n입력 : ";
		cin >> op;
		if (op == 1) {
			while (true) {
				cout << "관리자 비밀번호를 입력하세요(메인 화면으로 돌아가려면 -1 입력) : ";
				cin >> passwd;
				if (passwd == 1234) {
					managerMode();
					break;
				}
				else if (passwd == -1) {
					break;
				}
				else cout << "비밀번호가 틀립니다!\n\n";
			}
		}
		else if (op == 2) {
			customerMode();
		}

		else if (op == 3) {
			cout << "\n--------------프로그램을 종료합니다--------------\n";
			break;
		}
		else
			cout << "\n잘못 입력했습니다. 다시 입력해 주세요.\n\n";
	}
}
void ShoppingManager::managerMode() {
	bool x = true;
	while (x) {
		int op;
		cout << "\n< 쇼핑 관리자 모드 >\n[1] 상품 추가\n[2] 상품 삭제\n[3] 모든 상품 출력\n[4] 돌아가기\n입력 : ";
		cin >> op;
		while (true) {
			if (op == 1) {
				addProduct();
				break;
			}
			else if (op == 2) {
				deleteProduct();
				break;
			}
			else if (op == 3) {
				print(productList);
				break;
			}
			else if (op == 4) {
				x = false;
				cout << endl;
				break;
			}
			else {
				cout << "\n잘못 입력했습니다. 다시 입력해 주세요.\n";
				break;
			}
		}
	}
	

}
void ShoppingManager::customerMode() {
	bool x = true;
	while (x) {
		cout << "\n< 고객 모드 >\n[1] 상품 보기\n[2] 상품 검색\n[3] 장바구니 모드\n[4] 돌아가기\n입력 : ";
		int op;
		cin >> op;
		while (true) {
			if (op == 1) {
				print(productList);
				break;
			}
			else if (op == 2) {
				search();
				break;
			}
			else if (op == 3) {
				cartMode();
				break;
			}
			else if (op == 4) {
				x = false;
				cout << endl;
				break;
			}
			else {
				cout << "\n잘못 입력했습니다. 다시 입력해 주세요.\n";
				break;
			}

		}
	}
}
void ShoppingManager::cartMode() {
	bool x = true;
	while (x) {
		int op;
		cout << "\n< 장바구니 모드 >\n[1] 상품 보기\n[2] 장바구니에 담기\n[3] 장바구니 출력\n[4] 계산하기\n입력 : ";
		cin >> op;
		while (true) {
			
			if (op == 1) {
				print(productList);
				break;
			}
			else if (op == 2) {
				addToCart();
				break;
			}
			else if (op == 3) {
				print(cartList);
				break;
			}
			else if (op == 4) {
				print(cartList);
				calculate();
				cout << endl;
				x = false;
				break;
			}
			else {
				cout << "\n잘못 입력했습니다. 다시 입력해 주세요.\n";
				break;
			}
		}
	}
}
void ShoppingManager::addProduct(){
	cout << "새로운 상품을 추가합니다. 상품 이름 입력 시 no를 입력하면 빠져나갑니다." << endl;
	while (true) {
		Product p("", 0);		//임의의 Product 생성자 생성
		cin >> p;				//Product 생성자에 값 입력
		if (p.getName() == "no") {		//no가 입력되면 상품 입력 종료
			cout << "새로운 상품 추가 종료.\n\n";
			break;
		}
		else
			productList.push_back(p);	//no가 아니면 productList에 push_back
		cout << p.getName() << "를(을) 목록에 등록했습니다." << endl;
	}
}

void ShoppingManager::deleteProduct() {
	string name;
	bool x = true;
	cout << "\n상품명을 입력하세요 : ";
	cin.ignore();
	getline(cin, name);
	for (auto it = productList.begin(); it != productList.end(); it++) {	//vector의 처음부터 끝까지 반복
		if (it->getName() == name) {		//iterator의 name이 입력받은 값과 같으면
			cout << it->getName() << "를(을) 삭제합니다." << endl;
			productList.erase(it);			//productList에서 iterator가 가리키는 값 삭제
			x = false;
			break;
		}
	}
	if (x)
		cout << "\n입력하신 상품은 현재 등록되어 있지 않습니다." << endl;
	
}
void ShoppingManager::search() {
	bool x = true;
	cout << "\n상품명을 입력하세요 : ";
	string name;
	cin.ignore();
	getline(cin, name);
		for (auto it = productList.begin(); it != productList.end(); it++) {
			if (it->getName() == name) {
				cout << *it << endl;	//iterator가 가리키는 값(Product 객체) 출력
				x = false;
				break;
			}
		}

	if (x)
		cout << "\n입력하신 상품은 현재 등록되어 있지 않습니다." << endl;
}
void ShoppingManager::print(vector<Product> pList) {		//모든 객체 출력
	cout << endl;
	for (auto it = pList.begin(); it != pList.end(); it++)
		cout << *it << endl;
	cout <<"\n총 "<<pList.size()<<"가지의 상품"<<endl;		//size를 출력
}

void ShoppingManager::addToCart() {
	cin.ignore();
	while (true) {
		bool x = true;
		string name;
		int n;
		vector<Product>::iterator newit;		//새로운 iterator 생성(productList에서 cartList로 옮기기 위함)
		
		cout << "\n구매하고자 하는 상품 이름 입력(장바구니 담기 종료는 no 입력) : ";
		
		getline(cin, name);

		if (name == "no")
			break;
		else {

			for (auto it = productList.begin(); it != productList.end(); it++) {
				if (it->getName() == name) {	//찾고자하는 상품을 찾으면
					x = false;
					newit = it;		//현재 iterator를 아까 생성한 iterator에 복사
					break;
				}
			}
			if (x) {
				cout << "입력하신 상품은 현재 등록되어 있지 않습니다." << endl;
				
			}
			else {
				cout << "담을 수량 입력(" << newit->getName() << "의 남은 재고 : " << newit->getStock() << ") : ";
				cin >> n;
				if (n > newit->getStock())		//수량 예외처리
					cout << "\n현재 남은 재고보다 많은 수량을 입력했습니다. 다시 입력해주세요" << endl;
				else {
					cout << newit->getName() << " " << n << "개를 장바구니에 담았습니다." << endl;
					newit->setStock(n);		//setter함수를 이용해서 전체 제고 개수를 줄임
					Product cart(newit->getName(), newit->getPrice(), n);		//cart라는 새로운 객체 생성,newit를 활용해 인수 입력
					cartList.push_back(cart);		//cart객체를 cartList<vector>에 push_back
					cin.ignore();
				}
			}
		}
	}
}
void ShoppingManager::calculate() {
	int cost=0;		//cost 변수 초기화
	for (auto it = cartList.begin(); it != cartList.end(); it++) {		//cartList에 처음부터 끝까지
		cost += it->getPrice() * it->getStock();	//iterator가 가리키는 객체의 Price와 Stock을 곱해서 cost에 더함
	}
	cout << "\n총 " << cost << "원 결제 완료되었습니다.\n장바구니 모드를 종료합니다."<<endl;
	cartList.clear();		//장바구니를 새로 사용하기 위해 cartList<vector> clear
}
