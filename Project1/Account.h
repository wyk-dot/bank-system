#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

class SavingsAccount
{
public:
	SavingsAccount(int date, int id, double rate);
	void record(int date, double amount);
	void getId();
	void getBalance();
	void getRate();
	void show();
	void deposit(int date, double amount);
	void withdraw(int date, double amount);
	void settle(int date);
	~SavingsAccount();
protected:
	int id, LastDate;
	double balance, rate, accumulation;
};

#endif