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
	if (breakfastNo > 2) brFee = (breakfastNo - 2) * breakfastFee;			//조식인원이 3인 이상이면 brFee 게산, 아니면 brFee는 0 (조식 2인까지 무료)
	return fee + addFee + brFee;
}