#include "Standard.h"

Standard::Standard(int rn) {
	fee = 100;
	addFeePerPerson = 30;
	setroomNumber(rn);
}

double Standard::calculate() const {
	int addFee = 0;													//�߰� ��� -> ���ʿ� 0���� ����
	int brFee = breakfastNo*breakfastFee;							//���� ��� -> ���� �ο� �� * ���� ����
	if (people > 2) addFee = (people-2) * addFeePerPerson;			//�ο��� 3���̻��̸� addFee ���, �ƴϸ� addFee�� 0
	return fee + addFee + brFee;
}