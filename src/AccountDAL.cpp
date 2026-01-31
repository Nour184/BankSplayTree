#include "AccountDAL.h"

int AccountDAL::accountCount = 15815690;

AccountDAL::AccountDAL() {
	getAccountsFromCsv();
}

void AccountDAL::addAcount(Account acc)
{
	accounts->insert(acc);
}


void AccountDAL::addAccount(int creditScore, short age, short tenure, double balance, bool isActiveMember)
{
	// Input validation
	if (creditScore < 300 || creditScore > 850) {
		QMessageBox::warning(nullptr, "Invalid Input", "Credit score must be between 300 and 850.");
		return;
	}

	if (age <= 0 || age > 120) {
		QMessageBox::warning(nullptr, "Invalid Input", "Age must be a valid number between 1 and 120.");
		return;
	}

	if (tenure < 0 || tenure > 50) {
		QMessageBox::warning(nullptr, "Invalid Input", "Tenure must be between 0 and 50 years.");
		return;
	}

	if (balance < 0) {
		QMessageBox::warning(nullptr, "Invalid Input", "Balance cannot be negative.");
		return;
	}

	// Generate a new unique ID
	int newId = ++accountCount;

	// Create the account object
	Account newAccount(newId, creditScore, age, tenure, balance, isActiveMember);

	// Insert into the splay tree
	if (accounts) {
		accounts->insert(newAccount);

		qDebug() << "Inserted account with ID:" << newId;
		QMessageBox::information(nullptr, "Success",
			QString("Account with ID %1 added successfully.").arg(newId));
	}
	else {
		qWarning() << "Account tree is not initialized.";
		QMessageBox::critical(nullptr, "Error", "Failed to add account. Tree is not initialized.");
	}
}


Account* AccountDAL::getAccountyId(int id)
{
	auto foundNode = accounts->search(id);
	if (foundNode)
		return &foundNode->data;
	return nullptr;
}

bool AccountDAL::deleteAccount(int id)
{
	// auto instead of SplayTree<Account>::Node* for simplicity
	auto foundNode = accounts->search(id);
	if (foundNode)
	{
		accounts->erase(foundNode->data);
		return true;
	}
	return false;
}

bool AccountDAL::updateAccount(Account acc)
{
	auto foundNode = accounts->search(acc);
	if (foundNode)
	{
		foundNode->data = acc;  // Overwrite the old data with the new one
		return true;
	}
	return false;
}

vector<Account> AccountDAL::getAllAccounts()
{
	vector<Account> vec;
	accounts->collectInOrder(vec);
	return vec;
}


SplayTree<Account> AccountDAL::getDemoAccounts()
{
	SplayTree<Account> accounts;

	accounts.insert(Account(101, 750, 30, 5, 15000.50, true));
	accounts.insert(Account(102, 680, 25, 2, 2000.75, true));
	accounts.insert(Account(103, 720, 40, 10, 12000.00, false));
	accounts.insert(Account(104, 650, 35, 7, 8000.90, true));
	accounts.insert(Account(105, 100, 28, 3, 30000.60, true));
	accounts.insert(Account(106, 1000, 36, 5, 45230.75, true));
	accounts.insert(Account(107, 234, 42, 10, 12800.00, true));
	accounts.insert(Account(108, 123, 29, 2, 95320.10, true));
	accounts.insert(Account(109, 1023, 50, 12, 34000.50, true));
	accounts.insert(Account(110, 60, 23, 1, 18760.25, true));


	return accounts;
}

 SplayTree<Account>* AccountDAL::readAccountsFromCsv(const QString& filePath) {
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "Could not open file:" << filePath;
		return accounts;
	}

	QTextStream in(&file);
	bool firstLine = true; // Skip header

	while (!in.atEnd()) {
		QString line = in.readLine();
		if (firstLine) {
			firstLine = false;
			continue;
		}

		Account account(line);
		//if (account.isValid()) {
			accounts->insert(account);
		//}
	}
	
	file.close();
	
	qDebug() << "accounts in tree:" << accounts->nodeCount();
	
	return accounts;
}

void AccountDAL::getAccountsFromCsv()
{
	QString csvPath = /*QDir::currentPath()+*/ "C:/Users/lenovo thinkpad E15/Desktop/fundamentals c++/SplayTreeDemo/DummyData/SplayTreeBankAccounts.csv";
	this->accounts = readAccountsFromCsv(csvPath);
}

bool AccountDAL::isEmpty()
{
	return accounts->empty();
}
