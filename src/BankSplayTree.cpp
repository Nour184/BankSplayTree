#include<iostream>
#include <QString>   // For QString
#include <string>    // For std::string
#include "BankSplayTree.h"
#include <warning.h>
using namespace std;
BankSplayTree::BankSplayTree(QWidget *parent) : QMainWindow(parent)
{
   
    ui.setupUi(this);

    connect(ui.addAccountDashboard, &QPushButton::clicked, [this]() {
        ui.stackedDashboardPages->setCurrentIndex(0);  // Switch to add Account page
        connect(ui.createAccountButton, &QPushButton::clicked,
            this, &BankSplayTree::saveAccountData);
    });


    connect(ui.deleteAccountDashboard, &QPushButton::clicked, [this]() {
        ui.stackedDashboardPages->setCurrentIndex(1);  // Switch to delete Account page
        connect(ui.pushButtonDelete, &QPushButton::clicked,
            this, &BankSplayTree::deleteAccount);
    }); 

    connect(ui.searchAccountDashboard, &QPushButton::clicked, [this]() {
        ui.stackedDashboardPages->setCurrentIndex(3);  // Switch to search account page
        //ui.stackedSearchWidget->setCurrentIndex(0);
        connect(ui.searchAccountbutton, &QPushButton::clicked,
            this, &BankSplayTree::setAccountDetails);
    }); 
 
    connect(ui.treeDemoDashboard, &QPushButton::clicked, this, [this]() {
        ui.stackedDashboardPages->setCurrentIndex(2);
        openSplayDemo(); // Call your function here
    });
  
   

}


void BankSplayTree::saveAccountData()
{
    bool ageField_ok, tenureField_ok, balanceField_ok, CreditScoreField_ok;

   // QString nameField = ui.lineEditName->text();
   // string nameFeildStr = nameField.toStdString();

    QString ageField = ui.lineEditAge->text();
    short ageFieldVal = ageField.toShort(&ageField_ok);
    if (!ageField_ok) {
        qWarning() << "Invalid age:" << ageField;
    }

    QString tenureField = ui.lineEditTenure->text();
    short tenureFieldVal = tenureField.toShort(&tenureField_ok);
    if (!tenureField_ok) {
        qWarning() << "Invalid tenure:" << tenureField;
    }

    QString balanceField = ui.lineEditBalance->text();
    double balanceFieldVal = balanceField.toDouble(&balanceField_ok);
    if (!balanceField_ok) {
        qWarning() << "Invalid balance:" << balanceField;
    }

    QString CreditScoreField = ui.lineEditCreditScore->text();
    double CreditScoreFieldVal = CreditScoreField.toDouble(&CreditScoreField_ok);
    if (!CreditScoreField_ok) {
        qWarning() << "Invalid CreditScore:" << CreditScoreField;
    }
    /*    int customerID;
void AccountDAL::addAccount(int creditScore, short age, short tenure, double balance, bool isActiveMember)

*/
    accountDAL->addAccount(CreditScoreFieldVal, ageFieldVal, tenureFieldVal, balanceFieldVal, true);

    }

void BankSplayTree::setAccountDetails()
{
    // Get and validate input
    QString inputText = ui.lineEditAccount->text();
    bool conversionOK;
    int accountId = inputText.toInt(&conversionOK);

    if (!conversionOK) {
        qDebug() << "Invalid ID";
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric account ID.");
        // clearAccountDisplay(); // Uncomment if you have a method to clear previous UI fields
        return;
    }

    // Fetch account data
    Account* acc = accountDAL->getAccountyId(accountId);
    if (!acc) {
        qDebug() << "Account not found";
        QMessageBox::information(this, "Account Not Found",
            QString("No account found with ID: %1").arg(accountId));
        // clearAccountDisplay(); // Uncomment if needed
        return;
    }

    // Update all UI fields with null checks
    ui.labelCustomerId->setText(QString::number(accountId));
    ui.labelAge->setText(QString::number(acc->getAge()));
    ui.labelCreditScore->setText(QString::number(acc->getCreditScore()));
    ui.labelBalance->setText(QString::number(acc->getBalance(), 'f', 2));
    ui.labelTenure->setText(QString::number(acc->getTenure()));
    if (acc->isActive()) {
        ui.labelActivity->setText("This Account is Active");
        ui.labelActivity->setStyleSheet("color: #41cd52; font-weight: bold;"); // A nice "Success" Green
    }
    else {
        ui.labelActivity->setText("This Account is not Active");
        ui.labelActivity->setStyleSheet("color: #ff4d4d; font-weight: bold;"); // A bright "Warning" Red
    }

    QMessageBox::information(this, "Account Found",
        QString("Account ID %1 found and loaded.").arg(accountId));
}



//deleting an account logic


void BankSplayTree::deleteAccount()
{
    // Get text from QLineEdit
    QString inputText = ui.deleteAccountID->text(); // Replace with your actual QLineEdit name

    // Convert to int with validation
    bool conversionOK;
    int accountId = inputText.toInt(&conversionOK);

    if (!conversionOK) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid account ID.");
        qWarning() << "Invalid account ID entered.";
        return;
    }

    qDebug() << "Attempting to delete account ID:" << accountId;

    bool isDeleted = accountDAL->deleteAccount(accountId);
    if (isDeleted) {
        QMessageBox::information(this, "Success", "Account deleted successfully.");
        qDebug() << "Account +deleted successfully.";
    }
    else {
        QMessageBox::critical(this, "Error", "Account not found. Deletion failed.");
        qWarning() << "Account deletion failed. ID not found.";
    }
}

void BankSplayTree::openSplayDemo() {
    if (!demoWindow)
        demoWindow = new DemoWindow(accountDAL, this);


    demoWindow->show();
}



BankSplayTree::~BankSplayTree()
{}


