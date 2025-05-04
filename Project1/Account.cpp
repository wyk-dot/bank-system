#include "Account.h"
#include <iomanip>
#include <iostream>
#include <cmath>

//Account:

double Account::total = 0.0;

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

void Account::show() {
	cout << "#" << setw(15) << left << id;
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

//SavingsAccount:

SavingsAccount::SavingsAccount(Date date, string id, double rate) :Account(date, id), acc(date, 0)
{
	this->rate = rate;
	balance = 0, accumulation = 0;
	date.show();
	cout << "#" << id << " created" << endl;
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
	total += amount;
	acc.LastDate.setdate(date);
	date.show();
	Account::show();
	cout << setw(8) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::withdraw(Date date, double amount, string state)
{
	accumulation += (acc.getdate(date)) * balance;
	balance -= amount;
	total -= amount;
	acc.LastDate.setdate(date);
	date.show();
	Account::show();
	if (amount != 0) cout << "-";
	cout << setw(7) << amount << setw(8) << balance << state << endl;
}
void SavingsAccount::settle(Date date)
{
	int p = acc.LastDate.getyear();
	int c = date.getyear(), e = date.getmonth(), f = date.getday();
	if (p == c || e != 1 || f != 1) return;
	int h = acc.getdate(date);
	accumulation += (h)*balance;
	if ((p % 4 == 0 && p % 100 != 0) || p % 400 == 0)
	{
		accumulation = (accumulation)*rate / 366;
	}
	else accumulation = (accumulation)*rate / 365;
	balance += accumulation;
	total += accumulation;
	acc.LastDate.setdate(date);
	date.show();
	Account::show();
	cout << setw(8) << left << floor(accumulation * 100 + 0.5) / 100 << setw(8) <<
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
	date.show();
	cout << "#" << id << " created" << endl;
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
	total += amount;
	if (balance < 0) balance -= fabs(balance) * acc.LastDate.getdate(date) * rate;
	acc.LastDate.setdate(date);
	date.show();
	Account::show();
	cout << setw(8) << amount << setw(8) << balance << desc << endl;
}
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	if (balance < 0) balance -= fabs(balance) * acc.LastDate.getdate(date) * rate;
	balance -= amount;
	total -= amount;
	acc.LastDate.setdate(date);
	date.show();
	Account::show();
	if (amount != 0) cout << "-";
	cout << setw(7) << amount << setw(8) << balance << desc << endl;
}
void CreditAccount::settle(Date date)
{
	int a = acc.LastDate.getyear(), b = acc.LastDate.getmonth();
	if (b == date.getmonth() || date.getday() != 1) return;
	double amount = fabs(balance) * acc.LastDate.getdate(date) * rate;
	if (balance < 0) balance -= amount;
	total -= amount;
	date.show();
	Account::show();
	if (amount != 0) cout << "-";
	cout << setw(7) << left << floor(amount * 100 + 0.5) / 100 << setw(8) <<
		left << balance << "interest" << endl;
	if (a != date.getyear())
	{
		balance -= fee;
		total -= fee;
		date.show();
		Account::show();
		if (fee != 0) cout << "-";
		cout << setw(7) << left << fee << setw(8) <<
			left << balance << "annual fee" << endl;
		acc.LastDate.setdate(date);
	}
	acc.LastDate.setdate(date);
}

void CreditAccount::show()
{
	cout << id << setw(16) << right << "Balance: " << setw(6) << left << balance << "available credit: " << getAvailableCredit();
}

CreditAccount::~CreditAccount()
{
}


