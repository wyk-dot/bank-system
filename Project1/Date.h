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
	int getyear()const;
	int getmonth()const;
	int getday()const;
	int getmaxday();
	bool isleapyear();
	void show()const;
	int getdate(Date date)const;
	void setdate(Date date);
	static Date read();
	bool operator<(const Date& date2) const;
	bool operator==(const Date& date2) const;
	~Date();
protected:
	int year, month, day;
};

#endif