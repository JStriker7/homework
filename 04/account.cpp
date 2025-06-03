#include "account.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

// 初始化静态成员变量 total
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
        RATE = balance * days * rate; // RATE是利息
        // Only show interest line if there's actual interest
        if (RATE != 0) {
            balance += RATE;
            total += RATE;
            cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(2)
                << RATE << "\t" << fixed << setprecision(2) << balance
                << "\tinterest" << endl;
        }
    }

    if (date.getMonth() == 1 && date.getDay() == 1)  
    {
        
        balance -= fee;
        total -= fee;
        cout << date.toString() << "\t#" << id << "\t-" << (int)fee << "\t"<< fixed << setprecision(2) << balance << "\tannual fee" << endl;
    
    }
    lastDate = date;
}

void CreditAccount::show() const
{
    cout << id << "\tBalance: " << fixed << setprecision(2) << balance
        << "\tAvailable credit:" << fixed << setprecision(2) << (credit + balance);
}




// 构造函数
SavingsAccount::SavingsAccount(Date startDate, std::string id, double rate)
    : id(id), balance(0.0), rate(rate), lastDate(startDate), accumulation(0) {
    total += balance;
    cout << startDate.toString() << "\t#" << id << " created" << endl;
}

// 累加计算
double SavingsAccount::accumulate(Date date) {
    int days = Date(lastDate).daysBetween(Date(date)); // 调用修复后的Date类
    accumulation += days*balance;
    
    return accumulation;
}

// 存款操作
void SavingsAccount::deposit(Date date, double amount, std::string description) {
    accumulate(date);  // 更新累积金额
   
    balance += amount;
    total += amount;  // 更新所有账户总金额
    lastDate = date;  // 更新最后操作日期
    cout << date.toString() << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << description << endl;
  
}

// 取款操作
void SavingsAccount::withdraw(Date date, double amount, std::string description) {
    accumulate(date);  // 更新累积金额
  
    balance -= amount;
    total -= amount;  // 更新所有账户总金额
    lastDate = date;  // 更新最后操作日期
    cout << date.toString() << "\t#" << id << "\t-" << amount << "\t" << balance << "\t" << description << endl;

}

// 结算利息
// 在SavingsAccount类的settle函数中增加以下处理
void SavingsAccount::settle(Date date) {
    accumulate(date);  // 累加积数

    if (date.getMonth() == 1 && date.getDay() == 1) {
        double interest = accumulation * rate / 366;
    

    // 其他操作
    accumulation = 0;
    balance += interest;
    total += interest;

    cout << date.toString() << "\t#" << id << "\t" << fixed << setprecision(2)
        << interest << "\t" << fixed << setprecision(2) << balance
        << " interest" << endl;
}
    lastDate = date;
}

// 获取总金额
double SavingsAccount::getTotal() {
    return total;
}

// 显示账户信息
void SavingsAccount::show() const {
    cout << id << "\tBalance: " << fixed << setprecision(2) << balance;
}
