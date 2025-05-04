#include "Date.h"

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

Date::~Date()
{
}

