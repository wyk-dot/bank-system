#pragma once
#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "Date.h"

using namespace std;

class Accumulator
{
public:
	Accumulator(Date date, double value);
	double getSum(Date date)const;
	void change(Date date, double value);
	void reset(Date date, double value);
	~Accumulator();
	Date LastDate;
	double value;
	double sum;
};

#endif
