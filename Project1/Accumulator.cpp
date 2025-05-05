#include "Accumulator.h"

using namespace std;

double Accumulator::getSum(Date date)const
{
	return sum + LastDate.getdate(date) * value;
}
void Accumulator::change(Date date, double value)
{
	sum = getSum(date);
	LastDate.setdate(date);
	this->value = value;
}
void Accumulator::reset(Date date, double value)
{
	sum = 0;
	LastDate.setdate(date);
	this->value = value;
}

Accumulator::Accumulator(Date date, double value) :LastDate(date)
{
	this->value = value;
	this->sum = 0;
}

Accumulator::~Accumulator()
{
}

