#include "account.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double SavingsAccount::total = 0;
SavingsAccount::SavingsAccount(Date date, string id, double rate) :LastDate(date)
{
	this->id = id;
	this->rate = rate;
	balance = 0, accumulation = 0;
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << id << " created" << endl;
}

void SavingsAccount::record(Date date, double amount)
{
}

void SavingsAccount::getId()
{
	cout << id << endl;
}
void SavingsAccount::getBalance()
{
	cout << balance << endl;
}
void SavingsAccount::getRate()
{
	cout << rate << endl;
}
void SavingsAccount::show()
{
	cout << id << setw(16) << right << "Balance: " << balance;
}
void SavingsAccount::deposit(Date date, double amount, string state)
{
	accumulation += (getdate(LastDate, date)) * balance;
	balance += amount;
	LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << setw(8) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::withdraw(Date date, double amount, string state)
{
	accumulation += (getdate(LastDate, date)) * balance;
	balance -= amount;
	LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << "-" << setw(7) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::settle(Date date)
{
	accumulation += (getdate(LastDate, date)) * balance;
	if ((LastDate.getyear() % 4 == 0 && LastDate.getyear() % 100 != 0) || LastDate.getyear() % 400 == 0)
	{
		accumulation = (accumulation)*rate / 366;
	}
	else accumulation = (accumulation)*rate / 365;
	balance += accumulation;
	total += balance;
	LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday() <<
		"#" << setw(15) << left << id << setw(8) << left << floor(accumulation * 100 + 0.5) / 100 << setw(8) <<
		left << balance << "interest" << endl;
}
double SavingsAccount::getTotal()
{
	return total;
}
int SavingsAccount::getdate(Date LastDate, Date date)
{
	int year1 = LastDate.getyear(), month1 = LastDate.getmonth(), day1 = LastDate.getday()
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

SavingsAccount::~SavingsAccount() {}
