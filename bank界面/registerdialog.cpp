#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QDebug>
#include <QMessageBox>
#include "homepage.h"
RegisterDialog::RegisterDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_registerBtn_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();


    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写所有信息");
        return;
    }


    if (password != confirmPassword) {
        QMessageBox::warning(this, "提示", "两次密码输入不一致");
        return;
    }

    qDebug() << "注册成功";


    HomePage *home = new HomePage();
    home->show();

    this->close();
}

