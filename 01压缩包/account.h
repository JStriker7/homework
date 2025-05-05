
//声明类和变量函数
#ifndef ACCOUNT_H
#define ACCOUNT_H


class SavingsAccount
{
private:
	int id;
	double balance;
	double rate;
	int lastDate;
	double accumulation;
public:
	
	void record();
	double accumulate(int date);
	SavingsAccount(int date, int id, double rate);
	int getId();
	double getBalance();
	double getRate();
	void show();
	void deposit(int date, double amount);
	void withdraw(int date, double amount);
	void settle(int date);

	
};
#endif
