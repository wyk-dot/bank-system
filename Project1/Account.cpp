#include "Account.h"
#include <iomanip>
#include <iostream>
#include <cmath>

//Account:

Account::Account(Date date, string id)
{
	this->id = id;
}

void Account::record(Date date, double total, string desc)
{
}
void Account::error(string msg)const
{
}
string Account::getId()const
{
	return id;
}
double Account::getBalance()const
{
	return balance;
}

double Account::getTotal()
{
	return total;
}

Account::~Account()
{
}
/*void Account::show()
{
	cout << id;
}*/
//SavingsAccount:

SavingsAccount::SavingsAccount(Date date, string id, double rate) :Account(date, id), acc(date, 0)
{
	this->rate = rate;
	balance = 0, accumulation = 0;
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << id << " created" << endl;
}

void SavingsAccount::record(Date date, double amount)
{
}

void SavingsAccount::getRate()
{
	cout << rate << endl;
}

void SavingsAccount::deposit(Date date, double amount, string state)
{
	accumulation += (acc.getdate(date)) * balance;
	balance += amount;
	acc.LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << setw(8) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::withdraw(Date date, double amount, string state)
{
	accumulation += (acc.getdate(date)) * balance;
	balance -= amount;
	acc.LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << "-" << setw(7) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::settle(Date date)
{
	int h = acc.getdate(date);
	accumulation += (h)*balance;
	int p = acc.LastDate.getyear();
	if ((p % 4 == 0 && p % 100 != 0) || p % 400 == 0)
	{
		accumulation = (accumulation)*rate / 366;
	}
	else accumulation = (accumulation)*rate / 365;
	balance += accumulation;
	total += balance;
	acc.LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(9) << left << date.getday() <<
		"#" << setw(15) << left << id << setw(8) << left << floor(accumulation * 100 + 0.5) / 100 << setw(8) <<
		left << balance << "interest" << endl;
}

void SavingsAccount::show()
{
	cout << id << setw(16) << right << "Balance: " << balance;
}

SavingsAccount::~SavingsAccount()
{
}


//CreditAccount:

CreditAccount::CreditAccount(Date date, string id, double credit, double rate, double fee) :Account(date, id), acc(date, 0)
{
	this->credit = credit;
	this->rate = rate;
	this->fee = fee;
	balance = 0;
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << id << " created" << endl;
}

double CreditAccount::getDebt()const
{
	if (balance >= 0) return 0;
	else return balance;
}
double CreditAccount::getCredit()const
{
	return credit;
}
double CreditAccount::getRate()const
{
	return rate;
}
double CreditAccount::getFee()const
{
	return fee;
}
double CreditAccount::getAvailableCredit()const
{
	return balance + credit;
}
void CreditAccount::deposit(Date date, double amount, string desc)
{
	balance += amount;
	if (balance < 0) balance -= fabs(balance) * acc.LastDate.getdate(date) * rate;
	//cout << acc.LastDate.getdate(date) << " wuyinke" << endl;
	acc.LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << setw(8) << amount << setw(8) << balance << desc << endl;
}
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	if (balance < 0) balance -= fabs(balance) * acc.LastDate.getdate(date) * rate;
	balance -= amount;
	acc.LastDate.setdate(date);
	cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday()
		<< "#" << setw(15) << left << id << setw(8) << amount << setw(8) << balance << desc << endl;
}
void CreditAccount::settle(Date date)
{
	if (balance < 0) balance -= fabs(balance) * acc.LastDate.getdate(date) * rate;
	if (acc.LastDate.getyear() == date.getyear())
	{
		cout << date.getyear() << "-" << date.getmonth() << "-" << setw(8) << left << date.getday() <<
			"#" << setw(15) << left << id << "-" << setw(7) << left << fee << setw(8) <<
			left << balance << "interest" << endl;
		return;
	}
	else
	{
		balance -= fee;
		total += balance;
		cout << date.getyear() << "-" << date.getmonth() << "-" << setw(9) << left << date.getday() <<
			"#" << setw(15) << left << id << "-" << setw(7) << left << fee << setw(8) <<
			left << balance << "annual fee" << endl;
	}
}

void CreditAccount::show()
{
	cout << id << setw(16) << right << "Balance: " << balance << "available credit: " << getAvailableCredit();
}

CreditAccount::~CreditAccount()
{
}
