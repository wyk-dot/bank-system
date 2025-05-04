#include "Date.h"

using namespace std;

Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::getyear()
{
	return year;
}
int Date::getmonth()
{
	return month;
}
int Date::getday()
{
	return day;
}
void Date::setdate(Date date)
{
	this->year = date.getyear();
	this->month = date.getmonth();
	this->day = date.getday();
}

int Date::getdate(Date date)
{
	int year1 = this->getyear(), month1 = this->getmonth(), day1 = this->getday()
		, year2 = date.getyear(), month2 = date.getmonth(), day2 = date.getday();
	int d[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, t = 0;
	if (year1 == year2 && month1 == month2) return day2 - day1;
	else
	{
		if ((year1 % 4 == 0 && year1 % 100 != 0) || year1 % 400 == 0)
		{
			if (month1 == 2)
			{
				t += 29 - day1;
				month1++;
			}
			else
			{
				t += d[month1 - 1] - day1;
				month1++;
			}
		}
		else
		{
			t += d[month1 - 1] - day1;
			cout << t << endl;
			month1++;
		}

	}
	for (int i = year1;i <= year2;i++)
	{
		for (int k = month1;k <= 12;k++)
		{
			if (i == year2 && k == month2) return t + day2;
			if (((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) && k == 2)
			{
				t += 29;continue;
			}
			else t += d[k - 1];
		}
		month1 = 1;
	}
	return t;
}

Date::~Date()
{
}
