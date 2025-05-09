//step5.cpp

#include "account.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct deleter {

	template <class T> void operator () (T* p) { delete p; }

};


int main() {

	Date date(2008, 11, 1);//��ʼ����

	vector<Account*> accounts;//�����˻����飬Ԫ�ظ���Ϊ0

	//����֮ǰtxt�ı�������
	ifstream infile("commands.txt");//���ڴ��ļ��ж�ȡ����

	string line;

	while (getline(infile, line))
	{
		if (line.empty()) continue;

		istringstream iss(line);//��һ���ַ����а��ո������ȡ����/����

		char cmd;

		iss >> cmd;
		
		switch (cmd)
		{
			case 'a':
			{
				char type;
				string id;
				iss >> type >> id;
				if (type == 's')
				{
					double rate;
					iss >> rate;
					accounts.push_back(new SavingsAccount(date, id, rate));
				}
				else if(type=='c')
				{
					double credit, rate, fee;
					iss >> credit >> rate >> fee;
					accounts.push_back(new CreditAccount(date, id, credit, rate, fee));
				}
				break;
			}
			
			case 'd':
			{
				int index;
				double amount;
				string desc;
				iss >> index >> amount;
				getline(iss, desc);
				accounts[index]->deposit(date, amount, desc);
				break;
			}

			case 'w':
			{
				int index;
				double amount;
				string desc;
				iss >> index >> amount;
				getline(iss, desc);
				accounts[index]->withdraw(date, amount, desc);
				break;
			}

			case 'c':
			{
				int day;
				iss >> day;
				date = Date(date.getYear(), date.getMonth(), day);
				break;
			}
			
			case'n':
			{
				if (date.getMonth() == 12)
				{
					date = Date(date.getYear() + 1, 1, 1);
				}
				else 
				{
					date = Date(date.getYear(), date.getMonth() + 1, 1);
				}
					for (auto acc : accounts)
					acc->settle(date);
				break;
			}

			break;
		}
	}

	infile.close();


	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;

	char cmd;



		//��ʾ���ں��ܽ��

		date.show();

		cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";


		char type;

		int index, day;

		double amount, credit, rate, fee;

		string id, desc;

	

		Date date1, date2;

		cin >> cmd;

		ofstream outfile("commands.txt", ios::app);

		switch (cmd) {

		case 'a'://�����˻�

			cin >> type >> id;

			if (type == 's') {

				cin >> rate;

				accounts.push_back(new SavingsAccount(date, id, rate));

				outfile << "a s " << id << " " << rate << endl;

			}

			else {

				cin >> credit >> rate >> fee;

				accounts.push_back(new CreditAccount(date, id, credit, rate, fee));

				outfile << "a c " << id << " " << credit << " " << rate << " " << fee << endl;
			}
			

			break;

		case 'd'://�����ֽ�

			cin >> index >> amount;

			getline(cin, desc);

			accounts[index]->deposit(date, amount, desc);

			outfile << "d " << index << " " << amount << desc << endl;

			break;

		case 'w'://ȡ���ֽ�

			cin >> index >> amount;

			getline(cin, desc);

			accounts[index]->withdraw(date, amount, desc);

			outfile << "w " << index << " " << amount << desc << endl;

			break;

		case 's'://��ѯ���˻���Ϣ

			for (size_t i = 0; i < accounts.size(); i++) {

				cout << "[" << i << "] ";

				accounts[i]->show();

				cout << endl;

			}

			break;

		case 'c'://�ı�����

			cin >> day;
			
				date = Date(date.getYear(), date.getMonth(), day);

				outfile << "c " << day << endl;
			
			break;

		case 'n':
			if (date.getMonth() == 12) {
				date = Date(date.getYear() + 1, 1, 1);
			}
			else {
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}

			for (auto acc : accounts)
				acc->settle(date);

			outfile << "n" << endl;
			break;


		case 'q'://��ѯһ��ʱ���ڵ���Ŀ

			date1 = Date::read();

			date2 = Date::read();

			Account::query(date1, date2);

			break;

		}
		outfile.close();



	for_each(accounts.begin(), accounts.end(), deleter());

	return 0;

}