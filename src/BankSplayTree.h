#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BankSplayTree.h"
#include "AccountDAL.h"
#include "DemoWindow.h"

class BankSplayTree : public QMainWindow
{
    Q_OBJECT

public:
    BankSplayTree(QWidget *parent = nullptr);
    ~BankSplayTree();


private slots:

private:
    Ui::BankSplayTreeDemo ui;
    AccountDAL* accountDAL = new AccountDAL();
    DemoWindow* demoWindow = nullptr;
    void saveAccountData();
    void setAccountDetails();
    void deleteAccount();
    void openSplayDemo();

};
