#include "login.h"
#include "ui_login.h"
#include <QDate>
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);


}

Login::~Login()
{
    delete ui;
}

void Login::recLogin()
{
    this->show();
}

void Login::on_login_button2_clicked()
{

}

