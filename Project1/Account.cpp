#include "Account.h"
#include <iomanip>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>

//Account:

double Account::total = 0.0;
multimap<Date, AccountRecord> Account::recordMap;

Account::Account(Date date, string id)
{
	this->id = id;
	balance = 0;
	date.show();
	cout << "#" << id << " created" << endl;
}

void Account::record(Date date, double amount,double balance, string desc)
{
	AccountRecord a=AccountRecord(date, this, amount, balance, desc);
	recordMap.insert(make_pair(date, a));
	date.show();
	cout << "#" << setw(15) << left << id << setw(8) << amount << setw(8) << balance << desc << endl;
}
void Account::error(string msg)const
{
	cout << msg << endl;
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

void Account::query(Date& date1, Date& date2)
{
	multimap<Date, AccountRecord>::iterator a = recordMap.lower_bound(date1);
	multimap<Date, AccountRecord>::iterator b = recordMap.lower_bound(date2);
	multimap<Date, AccountRecord>::iterator p;
	for (p = a;p != b;p++)
	{
		p->second.show();
	}
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
}

void SavingsAccount::getRate()
{
	cout << rate << endl;
}

void SavingsAccount::deposit(Date date, double amount, string state)
{
	balance += amount;
	acc.change(date, balance);
	total += amount;
	record(date, amount, balance, state);
	acc.LastDate.setdate(date);
}
void SavingsAccount::withdraw(Date date, double amount, string state)
{
	if (amount > balance) throw AccountException("not enough money in SavingsAccount ", this);
	amount = -amount;
	balance += amount;
	acc.change(date, balance);
	total += amount;
	record(date, amount, balance, state);
	acc.LastDate.setdate(date);
}
void SavingsAccount::settle(Date date)
{
	int p = acc.LastDate.getyear();
	int c = date.getyear(), e = date.getmonth(), f = date.getday();
	if (p == c || e != 1 || f != 1 || balance==0) return;//balance等于零则退出是因为这时利息为零，没有进行后面步骤的必要。
	double accumulation=acc.getSum(date);
	if ((p % 4 == 0 && p % 100 != 0) || p % 400 == 0)
	{
		accumulation = (accumulation)*rate / 366;
	}
	else accumulation = (accumulation)*rate / 365;
	balance += accumulation;
	acc.reset(date, balance);
	total += accumulation;
	record(date, floor(accumulation * 100 + 0.5) / 100, balance, "interest");
}

void SavingsAccount::show()
{
	cout << " " << setw(12) << left << id << "Balance: " << balance;
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
	if (balance < 0) acc.change(date, balance * rate);
	acc.change(date, balance);
	total += amount;
	record(date, amount, balance, desc);
	acc.LastDate.setdate(date);
}
void CreditAccount::withdraw(Date date, double amount, string desc)
{
	if (amount > credit + balance) throw AccountException("not enough money in CreditAccount ", this);
	amount = -amount;
	balance += amount;
	if (balance < 0) acc.change(date, balance * rate);
	record(date, amount, balance, desc);
	total += amount;
	acc.LastDate.setdate(date);
}
void CreditAccount::settle(Date date)
{
	int a = acc.LastDate.getyear(), b = acc.LastDate.getmonth();
	if (b == date.getmonth() || date.getday() != 1) return;
	if (balance < 0)
	{
		double amount = acc.getSum(date);
		balance += amount;
		total += amount;
		if (balance < 0) acc.reset(date, balance * rate);
		else acc.reset(date, 0);
		record(date, floor(amount * 100 + 0.5) / 100, balance, "interest");
	}
	if (a != date.getyear())
	{
		balance -= fee;
		total -= fee;
		if (balance < 0) acc.reset(date, balance * rate);
		else acc.reset(date, 0);
		record(date, (-1)*fee, balance, "annual fee");
		return;
	}
}

void CreditAccount::show()
{
	cout << " " << setw(12) << left << id << "Balance: " << setw(6) << left << balance << "available credit: " << getAvailableCredit();
}

CreditAccount::~CreditAccount()
{
}

//AccountRecord:
AccountRecord::AccountRecord(const Date date, const Account* account, double amount, double balance, string desc)
	:date(date), account(account), amount(amount), balance(balance), desc(desc){ }
void AccountRecord::show()
{
	date.show();
	cout << "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

//AccountException
AccountException::AccountException(string err, Account* account) :runtime_error(err)
{
	this->account = account;

}
const char* AccountException::what()const
{
	cout << runtime_error::what() << "#";
	cout << account->getId() << endl;
	/*char* str = (char*)malloc(30 * sizeof(char));//在堆上分配数组内存，防止返回数组指针后指针指向不确定区域而引发错误。
	for (int i = 0; i < id.size();i++)
	{
		str[i] = id[i];
	}*/
	return "wuyinke";
}
AccountException::~AccountException()
{}


