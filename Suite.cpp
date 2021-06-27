#include "Suite.h"

Suite::Suite(int rn) {
	fee = 300;
	addFeePerPerson = 40;
	setroomNumber(rn);
}

double Suite::calculate() const {
	int addFee = 0;
	int brFee = 0 ;
	if (people > 2) addFee = (people - 2) * addFeePerPerson;
	if (breakfastNo > 2) brFee = (breakfastNo - 2) * breakfastFee;			//�����ο��� 3�� �̻��̸� brFee �Ի�, �ƴϸ� brFee�� 0 (���� 2�α��� ����)
	return fee + addFee + brFee;
}