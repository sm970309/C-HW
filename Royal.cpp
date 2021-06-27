#include "Royal.h"

Royal::Royal(int rn) {

	fee = 500;
	addFeePerPerson = 50;
	setroomNumber(rn);

}
void Royal::roomService(int rs) {
	serviceCost += double(rs);
}
double Royal::calculate() const {
	int addFee = 0;
	int brFee = 0;
	if (people > 2) addFee = (people - 2) * addFeePerPerson;			
	if (breakfastNo > 2) brFee = (breakfastNo - 2) * breakfastFee;		

	return fee + addFee + brFee + serviceCost;
}