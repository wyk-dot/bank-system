#include <iostream>
#include "account.h"
#include "Date.h"
#include <iomanip>
#include <cmath>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv)
{
	Date date(2008, 11, 1);//��ʼ����
	//���������˻�
	SavingsAccount accounts[] = {
		SavingsAccount(date, "S3755217", 0.015),
		SavingsAccount(date, "02342342", 0.015)
	};
	const int n = sizeof(accounts) / sizeof(SavingsAccount); //�˻�����
	//11�·ݵļ�����Ŀ
	accounts[0].deposit(Date(2008, 11, 5), 5000, "salary");
	accounts[1].deposit(Date(2008, 11, 25), 10000, "sell stock 0323");
	//12�·ݵļ�����Ŀ
	accounts[0].deposit(Date(2008, 12, 5), 5500, "salary");
	accounts[1].withdraw(Date(2008, 12, 20), 4000, "buy a laptop");
	//���������˻�����������˻���Ϣ
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		accounts[i].settle(Date(2009, 1, 1));
		accounts[i].show();
		cout << endl;
	}
	cout << "Total: " << SavingsAccount::getTotal() << endl;
	return 0;
}
