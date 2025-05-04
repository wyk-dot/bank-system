#include "Account.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

SavingsAccount::SavingsAccount(int date, int id, double rate)
{
	this->id = id;
	this->rate = rate;
	LastDate = date;
	balance = 0, accumulation = 0;
	cout << setw(8) << left << date << "#" << id << " is created" << endl;
}

void SavingsAccount::record(int date, double amount)
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
	cout << "#" << id << setw(16) << right << "Balance: " << balance;
}
void SavingsAccount::deposit(int date, double amount)
{
	accumulation += (date - LastDate) * balance;
	LastDate = date;
	balance += amount;
	cout << setw(8) << left << date << "#" << setw(15) << id <<
		setw(8) << left << amount << setw(8) << left << balance << endl;
}
void SavingsAccount::withdraw(int date, double amount)
{
	accumulation += (date - LastDate) * balance;
	LastDate = date;
	balance -= amount;
	cout << setw(8) << left << date << "#" << setw(15) << id << "-" <<
		setw(7) << left << amount << setw(8) << left << balance << endl;
}
void SavingsAccount::settle(int date)
{
	accumulation += (date - LastDate) * balance;
	accumulation = (accumulation)*rate / 365;
	balance += accumulation;
	LastDate = date;
	cout << setw(8) << left << date << "#" << setw(15) << id << setw(8)
		<< left << floor(accumulation * 100 + 0.5) / 100 << setw(8) << left << balance << endl;
}

SavingsAccount::~SavingsAccount() {}
