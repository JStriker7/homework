#include "account.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

// ��ʼ����̬��Ա���� total
double SavingsAccount::total = 0;

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
