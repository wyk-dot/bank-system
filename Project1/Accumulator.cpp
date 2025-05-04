#include "Accumulator.h"

using namespace std;

double Accumulator::getSum(Date date)const
{
	return sum;
}
void Accumulator::change(Date date, double value)
{
	LastDate.setdate(date);
	this->value = value;
}
void Accumulator::reset(Date date, double value)
{
	LastDate.setdate(date);
	this->value = value;
}

int Accumulator::getdate(Date date)
{
	return LastDate.getdate(date);
}

Accumulator::Accumulator(Date date, double value) :LastDate(date)
{
	this->value = value;
}

Accumulator::~Accumulator()
{
}

