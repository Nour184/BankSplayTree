#pragma once
#include "Account.h"
#include "SplayTree.h"
#include <vector>
#include <QString> 
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug> 
#include <QDir>
#include <QMessageBox>

using namespace std;

class AccountDAL
{
public:
	AccountDAL();

	void addAcount(Account acc);

	/*    
	int customerID;
    int creditScore;
    short age;
    short tenure;
    double balance;
    bool isActiveMember;
	*/
	void addAccount(int creditScore, short age, short tenure, double balance, bool isActiveMember);
	/*
	*  @param id of the desired account
	*  @return returns a pointer to the desired account
	*  @warning Splays the account to top
	*/
	Account* getAccountyId(int id);

	bool deleteAccount(int id);

	bool updateAccount(Account updated);

	vector<Account> getAllAccounts();

	SplayTree<Account> getDemoAccounts();
	void getAccountsFromCsv();

	SplayTree<Account>* readAccountsFromCsv(const QString& filePath);

	bool isEmpty();

private:
	SplayTree<Account>* accounts = new SplayTree<Account>;
	static int accountCount;
	 
};

