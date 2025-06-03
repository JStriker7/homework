#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "QDebug"
#include"QString"
#include "string"
#include "QMessageBox"
#include"login.h"
#include"QObject"
#include "logindialog.h"
#include "registerdialog.h"
#include"QDate"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_button_clicked()
{
       this->hide();
    LoginDialog *login = new LoginDialog();
    login->show();
}


void MainWindow::on_reg_button_clicked()
{
       this->hide();
    RegisterDialog *reg = new RegisterDialog();
    reg->show();
}

