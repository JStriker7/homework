#include "logindialog.h"
#include "ui_logindialog.h"
#include "homepage.h"
#include "QDebug"
#include"QMessageBox"
LoginDialog::LoginDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()

{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入用户名和密码");
        return;
    }

    HomePage *home = new HomePage();
    home->setCurrentUser(username);
    home->show();

    this->close();
}

