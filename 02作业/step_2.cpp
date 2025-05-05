// step_2.cpp

#include "account.h"
#include "date.h"
#include <iostream>
#include <sstream>  // ����ostringstream
#include <string>   // ����string����
#include <iostream>  // ����cout, endl��

using namespace std;



int main() {

	Date date(2008, 11, 1);//��ʼ����



	SavingsAccount accounts[] = {

	SavingsAccount(date, "S3755217", 0.015),

	SavingsAccount(date, "02342342", 0.015)

	};

	const int n = sizeof(accounts) / sizeof(SavingsAccount); //�˻�
	accounts[0].deposit(Date(2008, 11, 5), 5000, "salary");

	accounts[1].deposit(Date(2008, 11, 25), 10000, "sell stock 0323");



	accounts[0].deposit(Date(2008, 12, 5), 5500, "salary");

	accounts[1].withdraw(Date(2008, 12, 20), 4000, "buy a laptop");




	cout << endl;

	for (int i = 0; i < n; i++) {

		accounts[i].settle(Date(2009, 1, 1));

		accounts[i].show();

		cout << endl;

	}
	double total = SavingsAccount::getTotal();
	ostringstream oss;
	oss << total;  // ��ʹ��fixed��setprecision
	cout << "Total: " << oss.str() << endl;
	return 0;
	
}