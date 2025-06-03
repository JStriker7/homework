#include "account.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include<map>
using namespace std;

// ��ʼ����̬��Ա���� total
double Account::total = 0;

std::multimap<Date, AccountRecord> Account::recordMap;

void Account::query(const Date& start, const Date& end) {
    cout  << start.toString()  << end.toString() << endl;
  
    auto iter = recordMap.lower_bound(start);

    // �������ڷ�Χ�ڵ�������Ŀ
    while (iter != recordMap.end() && !(end < iter->first)) {
        iter->second.show();
        ++iter;
    }
}



void AccountRecord::show() const {
    cout << date.toString() << "\t#" << account->getId()
        << "\t" << (amount > 0 ? "" : "-") << fixed << setprecision(0) << fabs(amount)
        << "\t" << fixed << setprecision(0) << balance
        << "\t" << desc << endl;
}

void Account::record(const Date& date, double amount, double balance, const std::string& desc) {
    AccountRecord record(date, this, amount, balance, desc);
    recordMap.insert({date,record});
}

 double Account:: getTotal()
{
    return total;
}

CreditAccount::CreditAccount(Date date, std::string id, double credit, double rate, double fee) : Account(), balance(0), credit(credit), rate(rate), lastDate(date), fee(fee)
{
    this->id = id;
    total += balance;
    cout << lastDate.toString() << "\t#" << id << " created" << endl;
}

void CreditAccount::deposit(Date date, double amount, std::string desc)
{
   
    balance += amount;
    
    total += amount;
    cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(0) << amount << "\t" << fixed << setprecision(0) << balance << "\t" << desc << endl;
}

void CreditAccount::withdraw(Date date, double amount,std:: string desc)
{
   
    balance -= amount;
    lastDate = date;
    total -= amount;
    cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(0) << -amount << "\t" << fixed << setprecision(0) << balance << "\t" << desc << endl;
}


void CreditAccount::settle(Date date)
{
    int days = Date(lastDate).daysBetween(Date(date));

    double RATE = 0;
    if (balance < 0)
    {
        RATE = balance * days * rate; // RATE����Ϣ
        // Only show interest line if there's actual interest
        if (RATE != 0) {
            balance += RATE;
            total += RATE;
            cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(0) <<
                 RATE << "\t" << fixed << setprecision(0) << balance
                << "\tinterest" << endl;
        }
    }

    if (date.getMonth() == 1 && date.getDay() == 1)  
    {
        
        balance -= fee;
        total -= fee;
        cout << date.toString() << "\t#" << id << "\t-" << fixed << setprecision(0) << fee << "\t"<< fixed << setprecision(0) << balance << "\tannual fee" << endl;
    
    }
    lastDate = date;
}

void CreditAccount::show() const
{
    cout << id << "\tBalance: " << fixed << setprecision(0) << fixed <<  balance
        << "\tAvailable credit:" << fixed << setprecision(0) <<  (credit + balance);
}




// ���캯��
SavingsAccount::SavingsAccount(Date startDate, std::string id, double rate)
    : id(id), balance(0.0), rate(rate), lastDate(startDate), accumulation(0) {
    total += balance;
    cout << startDate.toString() << "\t#" << id << " created" << endl;
}

// �ۼӼ���
double SavingsAccount::accumulate(Date date) {
    int days = Date(lastDate).daysBetween(Date(date)); // �����޸����Date��
    accumulation += days*balance;
    
    return accumulation;
}

// ������
void SavingsAccount::deposit(Date date, double amount, std::string description) {
    accumulate(date);  // �����ۻ����
   
    balance += amount;
    total += amount;  // ���������˻��ܽ��
    lastDate = date;  // ��������������
    cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(0) << amount << "\t" << fixed << setprecision(0) << balance << "\t" << description << endl;
  
}

// ȡ�����
void SavingsAccount::withdraw(Date date, double amount, std::string description) {
    accumulate(date);  // �����ۻ����
  
    balance -= amount;
    total -= amount;  // ���������˻��ܽ��
    lastDate = date;  // ��������������
    cout << date.toString() << "\t#" << id << "\t-" << fixed << setprecision(0) << amount << "\t" << fixed << setprecision(0) << balance << "\t" << description << endl;

}

// ������Ϣ
// ��SavingsAccount���settle�������������´���
void SavingsAccount::settle(Date date) {
    accumulate(date);  // �ۼӻ���

    if (date.getMonth() == 1 && date.getDay() == 1) {
        double interest = accumulation * rate / 366;
    

    // ��������
    accumulation = 0;
    balance += interest;
    total += interest;

    cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(0)
        << interest << "\t" << fixed << setprecision(0) << balance
        << " interest" << endl;
}
    lastDate = date;
}

// ��ȡ�ܽ��
double SavingsAccount::getTotal() {
    return total;
}

// ��ʾ�˻���Ϣ
void SavingsAccount::show() const {
    cout << id << "\tBalance: " << fixed << setprecision(0) << balance;
}
