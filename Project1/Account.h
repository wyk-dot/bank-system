#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include "Date.h"

using namespace std;

class SavingsAccount
{
public:
	SavingsAccount(Date date, string id, double rate);
	void record(Date date, double amount);
	void getId();
	void getBalance();
	void getRate();
	void show();
	void deposit(Date date, double amount, string state);
	void withdraw(Date date, double amount, string state);
	void settle(Date date);
	static double getTotal();
	int getdate(Date LastDate, Date date);
	~SavingsAccount();
	static double total;
protected:
	string id;
	double balance, rate, accumulation;
	Date LastDate;
	string state;
};


#endif