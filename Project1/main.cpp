//step5.cpp

#include "account.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

vector<Account*> accounts;
Date date(2008, 11, 1);
char type, cmd;
int index, day;
double amount, credit, rate, fee;
string id, desc, ass;//定义一个ass作为辅助
Account* account;
Date date1, date2;

struct deleter {

	template <class T> void operator () (T* p) { delete p; }

};

void fx(string buffer);


int main() {

	cout << "whether restore the previous page?(y/n): ";
	
	cin >> cmd;
	fstream file;
	if (cmd == 'y')
	{
		file.open("./command.txt", ios::in);//
		if (file.is_open() == false)
		{
			cout << "Failure to open the file" << endl;
			return 0;
		}
		string buffer;
		while (getline(file, buffer))
		{
			if (buffer.size() == 1 && buffer[0] == '\n') break;
			fx(buffer);
 		}
		file.close();
		file.open("./command.txt", ios::app);
		if (file.is_open() == false)
		{
			cout << "Failure to open the file" << endl;
		}
	}
	else file.open("./command.txt", ios::out);

	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;

	

	do {

		//显示日期和总金额

		date.show();
		cout << "Total: " << Account::getTotal() << "\tcommand> ";
		cin >> cmd;
		switch (cmd) {
		case 'a'://增加账户
			cin >> type >> id;
			if (type == 's') {
				cin >> rate;
				account = new SavingsAccount(date, id, rate);
				file << "a" << " " << type << " " << id << " " << rate << "\n";
			}
			else {
				cin >> credit >> rate >> fee;
				account = new CreditAccount(date, id, credit, rate, fee);
				file << "a" << " " << type << " " << id << " " << credit << " " << rate << " " << fee << "\n";
			}
			accounts.push_back(account);
			break;
		case 'd'://存入现金
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			file << "d" << " " << index << " " << amount << " " << desc << "\n";
			break;
			
		case 'w'://取出现金
			try {
				cin >> index >> amount;
				getline(cin, desc);
				accounts[index]->withdraw(date, amount, desc);
				file << "w" << " " << index << " " << amount << " " << desc << "\n";
				break;
			}
			catch (AccountException e)
			{
				e.what();
			}
			break;
			
		case 's'://查询各账户信息
			for (size_t i = 0; i < accounts.size(); i++) {
				cout << "[" << i << "] ";
				accounts[i]->show();
				cout << endl;
			}
			file << "s" << "\n";
			break;
		case 'c'://改变日期
			cin >> day;
			if (day < date.getday())
				cout << "You cannot specify a previous day";
			else if (day > date.getmaxday())
				cout << "Invalid day";
			else
				date = Date(date.getyear(), date.getmonth(), day);
			file << "c" << " " << day << "\n";
			break;
		case 'n'://进入下个月
			if (date.getmonth() == 12)
				date = Date(date.getyear() + 1, 1, 1);
			else
				date = Date(date.getyear(), date.getmonth() + 1, 1);
			for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
				(*iter)->settle(date);
			file << "n" << "\n";
			break;
		case 'q'://查询一段时间内的账目
			try {
				date1 = Date::read();
				date2 = Date::read();
				Account::query(date1, date2);
				file << "q" << desc << "\n";
			}
			catch (const runtime_error& a)
			{
				
				getline(cin, ass);//ass这里将未读入的字符全部读入，防止循环多执行几次
				cout << a.what() << endl;
				break;
			}
			break;
		}
	} while (cmd != 'e');
	file.close();

	for_each(accounts.begin(), accounts.end(), deleter());

	return 0;

}

/*此函数用于将读取到的每一行文本内容buffer分散成单个字符串进行处理，然后重新执行上一次的操作*/
void fx(string buffer) 
{
	istringstream ss(buffer);
	vector<string> c;
	string a;
	while (getline(ss, a, ' '))
	{
		c.push_back(a);
	}
	int n = c.size();
	if (c[0] == "a")
	{
		if (c[1] == "s")
		{
			istringstream s1(c[3]);
			s1 >> rate;
			account = new SavingsAccount(date, c[2], rate);
			accounts.push_back(account);
		}
		else
		{
			istringstream s1(c[3]), s2(c[4]), s3(c[5]);
			s1 >> credit; s2 >> rate; s3 >> fee;
			account = new CreditAccount(date, c[2], credit, rate, fee);
			accounts.push_back(account);
		}
	}
	if (c[0] == "d")
	{
		istringstream s1(c[1]), s2(c[2]);
		s1 >> index; s2 >> amount;
		desc = c[3];
		accounts[index]->deposit(date, amount, desc);
	}
	if (c[0] == "w")
	{
		istringstream s1(c[1]), s2(c[2]);
		s1 >> index; s2 >> amount;
		desc = c[3];
		accounts[index]->withdraw(date, amount, desc);
	}
	if (c[0] == "s")
	{
		for (size_t i = 0; i < accounts.size(); i++) {
			cout << "[" << i << "] ";
			accounts[i]->show();
			cout << endl;
		}
	}
	if (c[0] == "c")
	{
		istringstream s1(c[1]);
		s1 >> day;
		if (day < date.getday())
			cout << "You cannot specify a previous day" << endl;
		else if (day > date.getmaxday())
			cout << "Invalid day";
		else
			date = Date(date.getyear(), date.getmonth(), day);
	}
	if (c[0] == "n")
	{
		if (date.getmonth() == 12)
			date = Date(date.getyear() + 1, 1, 1);
		else
			date = Date(date.getyear(), date.getmonth() + 1, 1);
		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
			(*iter)->settle(date);
	}
	if (c[0] == "q")
	{
		date1 = Date::read();
		date2 = Date::read();
		Account::query(date1, date2);
	}
}