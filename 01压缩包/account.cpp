//类构造函数和成员函数的实现
#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;

SavingsAccount::SavingsAccount(int date, int id, double rate) :id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	cout << date << "\t#" << id << " is created" << endl;
}

//每次取款或者存款都要执行一次accumulate函数 
double SavingsAccount::accumulate(int date)
{
	double a = balance * (date - lastDate);//计算按日增加的余额 
	accumulation += a; //这是关键点，累加利息总额，总后用其总数乘利率除365，得出最后总利息； 
	lastDate = date;
	return accumulation;
}

//每一次存款取款要经历的步骤：计算总利息，计算余额，改变最后一次余额变动时间； 

void SavingsAccount::deposit(int date, double amount)
{
	accumulate(date);

	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;

	cout << date << "\t#" << id <<"\t" << amount << "\t" << balance << endl;
}
void SavingsAccount::withdraw(int date, double amount)
{
	accumulate(date);
	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;
	balance -= amount;
	cout << date << "\t#" << id << "\t-" << amount << "\t" << balance << endl;
}
void SavingsAccount::settle(int date) {
	accumulate(date);  // 正确累加当前积数
	double interest = accumulation * rate / 365;
	accumulation = 0;  // 重置积数
	balance += interest;
	lastDate = date;   // 更新日期
	cout << date << "\t#" << id << "\t" << floor(interest* 100 + 0.5) / 100 << "\t" << balance << endl;
}

void SavingsAccount::show()
{
	cout << '#' << id << "\tBalance:" << balance;
}






