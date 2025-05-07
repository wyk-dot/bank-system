#include "Date.h"

using namespace std;

Date::Date()
{
	year = 2008;
	month = 11;
	day = 1;
}

Date::Date(int year, int month, int day)
{
	if (isValidDate(year, month, day) == false)
	{
		throw runtime_error("Date input error!");
		return;
	}
	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::getyear()const
{
	return year;
}
int Date::getmonth()const
{
	return month;
}
int Date::getday()const
{
	return day;
}
void Date::setdate(Date date)
{
	this->year = date.getyear();
	this->month = date.getmonth();
	this->day = date.getday();
}

int Date::getmaxday()
{
	int a = this->month, b = this->year;
	if (a == 1 || a == 3 || a == 5 || a == 7 || a == 8 || a == 10 || a == 12) return 30;
	else
	{
		if (a == 4 || a == 6 || a == 9 || a == 11) return 30;
		else
		{
			if ((b % 4 == 0 && b % 100 != 0) || b % 400 == 0) return 29;
			else return 28;
		}
	}
}

bool Date::isValidDate(int year, int month, int day) {
	if (year < 1900 || year > 2099) return false;
	if (month < 1 || month > 12) return false;
	int d[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
		d[1] = 29;
	}
	if (day < 1 || day > d[month - 1]) return false;
	return true;
}

bool Date::operator<(const Date& date2) const
{
	if (this->year < date2.year) return true;
	else if (this->year > date2.year) return false;
	if (this->month < date2.month) return true;
	else if (this->month > date2.month) return false;
	return this->day < date2.day;
}

bool Date::operator==(const Date& date2) const
{
	if (this->year == date2.getyear() && this->month == date2.getmonth() && this->day == date2.getday()) return true;
	else return false;
}

bool Date::isleapyear()
{
	int t = this->year;
	if ((t % 4 == 0 && t % 100 != 0) || t % 400 == 0)
	{
		return true;
	}
	else return false;
}

void Date::show()const
{
	int a = this->year, b = this->month, c = this->day;
	if (b >= 10)
	{
		cout << a << "-" << b << "-" << setw(8) << left << c;
	}
	else
	{
		cout << a << "-" << b << "-" << setw(9) << left << c;
	}
}

int Date::getdate(Date date)const//得到这一次日期和上一次日期之间相差的天数 
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

Date Date::read()
{
	int year, month, day;
	char a, b;
	cin >> year >> a >> month >> b >> day;
	return Date(year, month, day);
}

Date::~Date()
{
}