//�๹�캯���ͳ�Ա������ʵ��
#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;

SavingsAccount::SavingsAccount(int date, int id, double rate) :id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	cout << date << "\t#" << id << " is created" << endl;
}

//ÿ��ȡ����ߴ�Ҫִ��һ��accumulate���� 
double SavingsAccount::accumulate(int date)
{
	double a = balance * (date - lastDate);//���㰴�����ӵ���� 
	accumulation += a; //���ǹؼ��㣬�ۼ���Ϣ�ܶ�ܺ��������������ʳ�365���ó��������Ϣ�� 
	lastDate = date;
	return accumulation;
}

//ÿһ�δ��ȡ��Ҫ�����Ĳ��裺��������Ϣ���������ı����һ�����䶯ʱ�䣻 

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
	accumulate(date);  // ��ȷ�ۼӵ�ǰ����
	double interest = accumulation * rate / 365;
	accumulation = 0;  // ���û���
	balance += interest;
	lastDate = date;   // ��������
	cout << date << "\t#" << id << "\t" << floor(interest* 100 + 0.5) / 100 << "\t" << balance << endl;
}

void SavingsAccount::show()
{
	cout << '#' << id << "\tBalance:" << balance;
}






