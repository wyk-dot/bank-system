#pragma once
#pragma once
#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <iomanip>

class Date
{
public:
	Date();
	Date(int year, int month, int day);
	int getyear();
	int getmonth();
	int getday();
	int getmaxday();
	bool isleapyear();
	void show();
	int getdate(Date date);
	void setdate(Date date);
	~Date();
protected:
	int year, month, day;
};

#endif