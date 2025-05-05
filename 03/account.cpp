#include "account.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

// ��ʼ����̬��Ա���� total
double Account::total = 0;



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
    cout << date.toString() << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void CreditAccount::withdraw(Date date, double amount,std:: string desc)
{
   
    balance -= amount;
    lastDate = date;
    total -= amount;
    cout << date.toString() << "\t#" << id << "\t" << -amount << "\t" << balance << "\t" << desc << endl;
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
            cout << date.toString() << "\t#" << id << "\t" << RATE << "\t" << balance << "\t" << "interest" << endl;
        }
    }

    if (date.toString().find("1-1") != string::npos)  // Check if the date string contains "1-1"
    {
        // Charge annual fee
        balance -= fee;
        total -= fee;
        cout << date.toString() << "\t#" << id << "\t-" << (int)fee << "\t" << (int)balance << "\t" << "annual fee" << endl;
    
    }
    lastDate = date;
}

void CreditAccount::show()
{
    cout << id << "\tBalance: " << (int)balance << "\tAvailable credit:" << (int)credit + (int)balance;
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
    cout << date.toString() << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << description << endl;
  
}

// ȡ�����
void SavingsAccount::withdraw(Date date, double amount, std::string description) {
    accumulate(date);  // �����ۻ����
  
    balance -= amount;
    total -= amount;  // ���������˻��ܽ��
    lastDate = date;  // ��������������
    cout << date.toString() << "\t#" << id << "\t-" << amount << "\t" << balance << "\t" << description << endl;

}

// ������Ϣ
// ��SavingsAccount���settle�������������´���
void SavingsAccount::settle(Date date) {
    accumulate(date);  // �ۼӻ���
    double interest = accumulation * rate / 366;

    

    // ���ʱǿ�Ʊ�����λС��
    cout << fixed << setprecision(2);
    ostringstream oss;
    oss << fixed << setprecision(2) << interest; // �ȸ�ʽ��Ϊ��λС��
    string interestStr = oss.str();
    // ȥ��ĩβ�����С���㣨�����С�����֣�
    interestStr.erase(interestStr.find_last_not_of('0') + 1, string::npos);
    if (interestStr.back() == '.') {
        interestStr.pop_back(); // ȥ�������С����
    }

    // ��������
    accumulation = 0;
    balance += interest;
    total += interest;

    cout << date.toString() << "\t#" << id << "\t" <<interestStr << "\t" <<fixed << setprecision(1) <<balance << "\t" << "interest" << endl;
}

// ��ȡ�ܽ��
double SavingsAccount::getTotal() {
    return total;
}

// ��ʾ�˻���Ϣ
void SavingsAccount::show() const {
    cout << "" << id << "\tBalance: " << fixed << setprecision(1) << balance ;
}
