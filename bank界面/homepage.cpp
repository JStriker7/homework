#include "homepage.h"
#include "ui_homepage.h"
#include <QDate>
#include"QDebug"
#include <QMessageBox>
#include <algorithm>
#include <QDateTime>
#include <QString>
#include <QVector>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->accountTypeComboBox->addItem("储蓄账户");
    ui->accountTypeComboBox->addItem("信用账户");

    connect(ui->accountTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &HomePage::updateBalanceUI);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::setCurrentUser(const QString &username)
{
    currentUser = username;
    if (!savingsBalances.contains(username)) {
        savingsBalances[username] = 0.0;
    }
    if (!creditBalances.contains(username)) {
        creditBalances[username] = 0.0;
    }
    updateBalanceUI();
}

QString HomePage::getCurrentAccountType()
{
    return ui->accountTypeComboBox->currentText();
}

double& HomePage::getCurrentBalance()
{
    if (getCurrentAccountType() == "储蓄账户") {
        return savingsBalances[currentUser];
    } else {
        return creditBalances[currentUser];
    }
}

void HomePage::updateBalanceUI()
{
    double balance = getCurrentBalance();
    ui->balanceLabel->setText(QString("当前余额：%1元").arg(balance));
}

void HomePage::on_createAccountBtn_clicked()
{
        QMessageBox::information(this, "账户创建", "当前账户类型已启用。");
}


void HomePage::on_depositBtn_clicked()
{
    double amount = ui->amountEdit->text().toDouble();
    getCurrentBalance() += amount;
    QDateTime selectedTime(ui->dateEdit->date());
    transactions.append({currentUser, getCurrentAccountType(), amount, "存款", selectedTime});
    updateBalanceUI();
}


void HomePage::on_withdrawBtn_clicked()
{
    double amount = ui->amountEdit->text().toDouble();
    double& balance = getCurrentBalance();
    if (balance >= amount) {
        balance -= amount;
        QDateTime selectedTime(ui->dateEdit->date());  // 使用界面选择的时间
        transactions.append({currentUser, getCurrentAccountType(), -amount, "取款", selectedTime});
    } else {
        QMessageBox::warning(this, "错误", "余额不足，无法取款。\n");
    }
    updateBalanceUI();
}


void HomePage::on_repayBtn_clicked()
{
    if (getCurrentAccountType() != "信用账户") {
        QMessageBox::information(this, "提示", "还款只能用于信用账户");
        return;
    }
    double amount = ui->amountEdit->text().toDouble();
    creditBalances[currentUser] += amount;
    QDateTime selectedTime(ui->dateEdit->date());  // 使用界面选择的时间
    transactions.append({currentUser, "信用账户", amount, "还款", selectedTime});
    updateBalanceUI();
}

void HomePage::on_queryBtn_clicked()
{
    int year = ui->queryDateEdit->date().year();
    int month = ui->queryDateEdit->date().month();
    bool sortByAmount = ui->amountSortCheckBox->isChecked();

    queryTransactionsByMonth(year, month, sortByAmount);
}

void HomePage::queryTransactionsByMonth(int year, int month, bool sortByAmount)
{
    QVector<Transaction> results;

    for (const auto& t : transactions) {
        if (t.username == currentUser &&
            t.time.date().year() == year &&
            t.time.date().month() == month) {
            results.append(t);
        }
    }

    if (sortByAmount) {
        std::sort(results.begin(), results.end(), [](const Transaction& a, const Transaction& b) {
            return std::abs(a.amount) > std::abs(b.amount);  // 按金额降序
        });
    } else {
        std::sort(results.begin(), results.end(), [](const Transaction& a, const Transaction& b) {
            return a.time < b.time;  // 按时间升序
        });
    }

    QString resultText = QString("【%1年%2月交易记录】\n").arg(year).arg(month);
    for (const auto& t : results) {
        resultText += QString("[%1] [%2] %3 元 - %4\n")
                          .arg(t.time.toString("yyyy-MM-dd hh:mm"))
                          .arg(t.accountType)
                          .arg(t.amount, 0, 'f', 2)
                          .arg(t.operation);
    }

    QMessageBox::information(this, "交易记录", resultText);
}



void HomePage::on_queryStatsBtn_clicked()
{
    int year = ui->statsDateEdit->date().year();
    int month = ui->statsDateEdit->date().month();

    // 储蓄账户统计
    double income_savings = 0.0;
    double expense_savings = 0.0;
    int count_savings = 0;

    // 信用账户统计
    double income_credit = 0.0;
    double expense_credit = 0.0;
    int count_credit = 0;

    for (const auto& t : transactions) {
        if (t.username == currentUser &&
            t.time.date().year() == year &&
            t.time.date().month() == month) {

            if (t.accountType == "储蓄账户") {
                count_savings++;
                if (t.amount > 0)
                    income_savings += t.amount;
                else
                    expense_savings += -t.amount;
            } else if (t.accountType == "信用账户") {
                count_credit++;
                if (t.amount > 0)
                    income_credit += t.amount;
                else
                    expense_credit += -t.amount;
            }
        }
    }

    QString result = QString("【%1年%2月账户统计】\n\n"
                             "【储蓄账户】\n"
                             "总收入：%3 元\n"
                             "总支出：%4 元\n"
                             "交易笔数：%5 笔\n\n"
                             "【信用账户】\n"
                             "总收入：%6 元\n"
                             "总支出：%7 元\n"
                             "交易笔数：%8 笔")
                         .arg(year)
                         .arg(month)
                         .arg(income_savings, 0, 'f', 2)
                         .arg(expense_savings, 0, 'f', 2)
                         .arg(count_savings)
                         .arg(income_credit, 0, 'f', 2)
                         .arg(expense_credit, 0, 'f', 2)
                         .arg(count_credit);

    QMessageBox::information(this, "账户统计", result);
}
