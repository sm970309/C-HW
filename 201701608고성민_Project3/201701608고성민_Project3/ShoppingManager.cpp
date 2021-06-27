#include "ShoppingManager.h"


ostream& operator <<(ostream& stream, const Product& p) {		//�����ڸ� ����ؼ� �׸���� �����Ͽ���.


	stream << "��ǰ�� : ";
	stream.width(20);
	stream << left << p.name;
	stream << "���� : ";
	stream.width(10);
	stream << right << p.price << "�� ";
	stream << " ���/���� : " << p.stock << "��";
	return stream;
}
istream& operator >>(istream& ins, Product& p) {

	cout << "\n��ǰ �̸� �Է� : ";
	ins.ignore();
	getline(ins,p.name);
	if (p.name != "no") {				
		cout << "��ǰ ���� �Է� : ";
		ins >> p.price;
	}
	return ins;
}
ShoppingManager::ShoppingManager(const string fn) {
	ifstream fin;
	fin.open(fn);
	while (fin.eof() == false) {	//������ ������ �ݺ�
		string n;
		getline(fin, n);		//���پ� �о����

		//substr(index1,index2) -> index1���� index2���� ����
		string fisrt = n.substr(0, n.find(";"));		//0�� �ε������� ;��ġ�� �ε��� ���� first�� ����
		int second = stoi(n.substr(n.find(";") + 1));	//;��ġ �ε���+1 ���� ������ second�� ����
		
		//Product ������ �����
		Product product(fisrt, second);					//first -> ��ǰ�� , second -> ���� (stoi�� intŸ������ ����)
		productList.push_back(product);					//vector�� push_back
	}
	fin.close();
}

void ShoppingManager::mainMenu() {
	
	while (true) {
		int op, passwd;
		cout << "<< INU ���ο� ���� ���� ȯ���մϴ�! >>" << endl;
		cout << "[1] ���� ������ ���\n[2] �����\n[3] ����\n�Է� : ";
		cin >> op;
		if (op == 1) {
			while (true) {
				cout << "������ ��й�ȣ�� �Է��ϼ���(���� ȭ������ ���ư����� -1 �Է�) : ";
				cin >> passwd;
				if (passwd == 1234) {
					managerMode();
					break;
				}
				else if (passwd == -1) {
					break;
				}
				else cout << "��й�ȣ�� Ʋ���ϴ�!\n\n";
			}
		}
		else if (op == 2) {
			customerMode();
		}

		else if (op == 3) {
			cout << "\n--------------���α׷��� �����մϴ�--------------\n";
			break;
		}
		else
			cout << "\n�߸� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���.\n\n";
	}
}
void ShoppingManager::managerMode() {
	bool x = true;
	while (x) {
		int op;
		cout << "\n< ���� ������ ��� >\n[1] ��ǰ �߰�\n[2] ��ǰ ����\n[3] ��� ��ǰ ���\n[4] ���ư���\n�Է� : ";
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
				cout << "\n�߸� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���.\n";
				break;
			}
		}
	}
	

}
void ShoppingManager::customerMode() {
	bool x = true;
	while (x) {
		cout << "\n< �� ��� >\n[1] ��ǰ ����\n[2] ��ǰ �˻�\n[3] ��ٱ��� ���\n[4] ���ư���\n�Է� : ";
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
				cout << "\n�߸� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���.\n";
				break;
			}

		}
	}
}
void ShoppingManager::cartMode() {
	bool x = true;
	while (x) {
		int op;
		cout << "\n< ��ٱ��� ��� >\n[1] ��ǰ ����\n[2] ��ٱ��Ͽ� ���\n[3] ��ٱ��� ���\n[4] ����ϱ�\n�Է� : ";
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
				cout << "\n�߸� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���.\n";
				break;
			}
		}
	}
}
void ShoppingManager::addProduct(){
	cout << "���ο� ��ǰ�� �߰��մϴ�. ��ǰ �̸� �Է� �� no�� �Է��ϸ� ���������ϴ�." << endl;
	while (true) {
		Product p("", 0);		//������ Product ������ ����
		cin >> p;				//Product �����ڿ� �� �Է�
		if (p.getName() == "no") {		//no�� �ԷµǸ� ��ǰ �Է� ����
			cout << "���ο� ��ǰ �߰� ����.\n\n";
			break;
		}
		else
			productList.push_back(p);	//no�� �ƴϸ� productList�� push_back
		cout << p.getName() << "��(��) ��Ͽ� ����߽��ϴ�." << endl;
	}
}

void ShoppingManager::deleteProduct() {
	string name;
	bool x = true;
	cout << "\n��ǰ���� �Է��ϼ��� : ";
	cin.ignore();
	getline(cin, name);
	for (auto it = productList.begin(); it != productList.end(); it++) {	//vector�� ó������ ������ �ݺ�
		if (it->getName() == name) {		//iterator�� name�� �Է¹��� ���� ������
			cout << it->getName() << "��(��) �����մϴ�." << endl;
			productList.erase(it);			//productList���� iterator�� ����Ű�� �� ����
			x = false;
			break;
		}
	}
	if (x)
		cout << "\n�Է��Ͻ� ��ǰ�� ���� ��ϵǾ� ���� �ʽ��ϴ�." << endl;
	
}
void ShoppingManager::search() {
	bool x = true;
	cout << "\n��ǰ���� �Է��ϼ��� : ";
	string name;
	cin.ignore();
	getline(cin, name);
		for (auto it = productList.begin(); it != productList.end(); it++) {
			if (it->getName() == name) {
				cout << *it << endl;	//iterator�� ����Ű�� ��(Product ��ü) ���
				x = false;
				break;
			}
		}

	if (x)
		cout << "\n�Է��Ͻ� ��ǰ�� ���� ��ϵǾ� ���� �ʽ��ϴ�." << endl;
}
void ShoppingManager::print(vector<Product> pList) {		//��� ��ü ���
	cout << endl;
	for (auto it = pList.begin(); it != pList.end(); it++)
		cout << *it << endl;
	cout <<"\n�� "<<pList.size()<<"������ ��ǰ"<<endl;		//size�� ���
}

void ShoppingManager::addToCart() {
	cin.ignore();
	while (true) {
		bool x = true;
		string name;
		int n;
		vector<Product>::iterator newit;		//���ο� iterator ����(productList���� cartList�� �ű�� ����)
		
		cout << "\n�����ϰ��� �ϴ� ��ǰ �̸� �Է�(��ٱ��� ��� ����� no �Է�) : ";
		
		getline(cin, name);

		if (name == "no")
			break;
		else {

			for (auto it = productList.begin(); it != productList.end(); it++) {
				if (it->getName() == name) {	//ã�����ϴ� ��ǰ�� ã����
					x = false;
					newit = it;		//���� iterator�� �Ʊ� ������ iterator�� ����
					break;
				}
			}
			if (x) {
				cout << "�Է��Ͻ� ��ǰ�� ���� ��ϵǾ� ���� �ʽ��ϴ�." << endl;
				
			}
			else {
				cout << "���� ���� �Է�(" << newit->getName() << "�� ���� ��� : " << newit->getStock() << ") : ";
				cin >> n;
				if (n > newit->getStock())		//���� ����ó��
					cout << "\n���� ���� ����� ���� ������ �Է��߽��ϴ�. �ٽ� �Է����ּ���" << endl;
				else {
					cout << newit->getName() << " " << n << "���� ��ٱ��Ͽ� ��ҽ��ϴ�." << endl;
					newit->setStock(n);		//setter�Լ��� �̿��ؼ� ��ü ���� ������ ����
					Product cart(newit->getName(), newit->getPrice(), n);		//cart��� ���ο� ��ü ����,newit�� Ȱ���� �μ� �Է�
					cartList.push_back(cart);		//cart��ü�� cartList<vector>�� push_back
					cin.ignore();
				}
			}
		}
	}
}
void ShoppingManager::calculate() {
	int cost=0;		//cost ���� �ʱ�ȭ
	for (auto it = cartList.begin(); it != cartList.end(); it++) {		//cartList�� ó������ ������
		cost += it->getPrice() * it->getStock();	//iterator�� ����Ű�� ��ü�� Price�� Stock�� ���ؼ� cost�� ����
	}
	cout << "\n�� " << cost << "�� ���� �Ϸ�Ǿ����ϴ�.\n��ٱ��� ��带 �����մϴ�."<<endl;
	cartList.clear();		//��ٱ��ϸ� ���� ����ϱ� ���� cartList<vector> clear
}
