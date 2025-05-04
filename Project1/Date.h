#pragma once
#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date
{
public:
	Date(int year, int month, int day);
	int getyear();
	int getmonth();
	int getday();
	int getdate(Date date);
	void setdate(Date date);
	~Date();
protected:
	int year, month, day;
};

#endif