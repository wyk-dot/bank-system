#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Date.h"
#include "Accumulator.h"
#include <iomanip>
#include <cmath>

using namespace std;

//Account:

class Account
{
public:
	Account(Date date, string id);
	void record(Date date, double total, string desc);
	void error(string msg)const;
	string getId()const;
	double getBalance()const;
	//virtual void show();
	static double getTotal();
	~Account();
protected:
	string id;
	double balance;
	static double total;
};

double Account::total = 0;

//SavingsAccount:

class SavingsAccount :public Account
{
public:
	SavingsAccount(Date date, string id, double rate);
	void record(Date date, double amount);
	void getRate();
	void deposit(Date date, double amount, string state);
	void withdraw(Date date, double amount, string state);
	void settle(Date date);
	void show();
	~SavingsAccount();
protected:
	Accumulator acc;
	double rate, accumulation;
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