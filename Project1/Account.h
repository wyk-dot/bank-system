#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Accumulator.h"
#include <vector>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

class Account;

//AccountRecord:
class AccountRecord
{
public:
	AccountRecord(const Date date, const Account* account, double amount, double balance, string desc);
	void show();
private:
	Date date;
	const Account* account;
	double amount;
	double balance;
	string desc;
};

//Account:

class Account
{
public:
	Account(Date date, string id);
	virtual void record(Date date, double amount, double balance, string desc);
	void error(string msg)const;
	string getId()const;
	virtual void show();
	virtual void deposit(Date date, double amount, string state) = 0;
	virtual void withdraw(Date date, double amount, string state) = 0;
	virtual void settle(Date date) = 0;
	double getBalance()const;
	static void query(Date date1, Date date2);
	static double getTotal();
	~Account();
protected:
	string id;
	double balance;
	static double total;
	static multimap<Date, AccountRecord> recordMap;
};

//SavingsAccount:

class SavingsAccount :public Account
{
public:
	SavingsAccount(Date date, string id, double rate);
	//void record(Date date, double amount);
	void getRate();
	void deposit(Date date, double amount, string state);
	void withdraw(Date date, double amount, string state);
	void settle(Date date);
	void show();
	~SavingsAccount();
protected:
	Accumulator acc;
	double rate;
};

//CreditAccount:

class CreditAccount :public Account
{
public:
	CreditAccount(Date date, string id, double credit, double rate, double fee);
	double getDebt()const;
	double getCredit()const;
	double getRate()const;
	double getFee()const;
	double getAvailableCredit()const;
	void deposit(Date date, double amount, string desc);
	void withdraw(Date date, double amount, string desc);
	void settle(Date date);
	void show();
	~CreditAccount();
protected:
	Accumulator acc;
	double credit;
	double rate;
	double fee;
};

#endif