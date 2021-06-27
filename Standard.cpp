#include "Standard.h"

Standard::Standard(int rn) {
	fee = 100;
	addFeePerPerson = 30;
	setroomNumber(rn);
}

double Standard::calculate() const {
	int addFee = 0;													//추가 요금 -> 최초에 0으로 설정
	int brFee = breakfastNo*breakfastFee;							//조식 요금 -> 조식 인원 수 * 조식 가격
	if (people > 2) addFee = (people-2) * addFeePerPerson;			//인원이 3인이상이면 addFee 계산, 아니면 addFee는 0
	return fee + addFee + brFee;
}