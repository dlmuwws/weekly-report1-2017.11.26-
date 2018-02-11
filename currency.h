#pragma once
#ifndef currency_
#define currency_
#include<iostream>
using namespace std;
#include"myException.h"

enum signType { plus, minus };

class currency {
	friend ostream& operator<<(ostream& out, const currency& x);
public:
	currency(signType sign =signType::plus, unsigned long dollars = 0, unsigned int cents = 0);
	~currency() {}
	void setValue(signType sign, unsigned long dollars, unsigned int cents) ;
	void setValue(double);
	
	signType getSignType() const {
		if (amount > 0)return signType::plus; 
		else
		{
			return signType::minus;
		}
	};
	unsigned long getDollars() const {
		if (amount < 0) return(-amount / 100); 
		else
		{
			return amount / 100;
		}
	};
	unsigned int getCents() const{
		if (amount < 0) return(-amount-getDollars()*100);
		else
		{
			return amount - getDollars() * 100;;
		}
	};
	currency operator+(const currency &x) ;
	currency& operator+=(const currency &x) { amount += x.amount; return*this; };
	//void output(ostream&) const;
private:

	long amount;
};
currency::currency(signType sign, unsigned long dollars, unsigned int cents)
{
	setValue(sign, dollars, cents);
}
void currency::setValue(signType sign, unsigned long dollars, unsigned int cents) {
	if (cents > 99) {
		throw illegalParameterValue("Cents should be <100");
	}
	amount = dollars * 100 + cents;
	if (sign == signType::minus)
		amount = -amount;
}
void currency::setValue(double amout) {
	if (amout < 0) {
	//	Sign = signType::minus;
	//	amout = -amout;
		amount = (long)((amout - 0.001) * 100);
	}
	else
	{
		amount = (long)((amout + 0.001) * 100);
	}
	
}
inline currency currency::operator+(const currency & x)
{	
	currency result;
	result.amount = amount + x.amount;
	return result;
	
}
ostream& operator<<(ostream& out, const currency& x) {
	long theAmount = x.amount;
	if (theAmount < 0)
	{
		cout << '-';
		theAmount = -theAmount;
	}
	long dollars = theAmount / 100;
	cout << '$' << dollars << '.';
	int cents = theAmount  - dollars * 100;
	if (cents < 10)cout << '0';
	cout << cents;
	return out; 
}
#endif