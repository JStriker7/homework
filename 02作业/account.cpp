#include "account.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

// 初始化静态成员变量 total
double SavingsAccount::total = 0;

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
    double interest = accumulation * rate / 366;

    

    // 输出时强制保留两位小数
    cout << fixed << setprecision(2);
    ostringstream oss;
    oss << fixed << setprecision(2) << interest; // 先格式化为两位小数
    string interestStr = oss.str();
    // 去掉末尾的零和小数点（如果无小数部分）
    interestStr.erase(interestStr.find_last_not_of('0') + 1, string::npos);
    if (interestStr.back() == '.') {
        interestStr.pop_back(); // 去掉多余的小数点
    }

    // 其他操作
    accumulation = 0;
    balance += interest;
    total += interest;

    cout << date.toString() << "\t#" << id << "\t" <<interestStr << "\t" <<fixed << setprecision(1) <<balance << "\t" << "interest" << endl;
}

// 获取总金额
double SavingsAccount::getTotal() {
    return total;
}

// 显示账户信息
void SavingsAccount::show() const {
    cout << "" << id << "\tBalance: " << fixed << setprecision(1) << balance ;
}
