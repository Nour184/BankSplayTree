#pragma once
#include <iostream>
#include <QStringList>
#include <QMessageBox>

class Account {
private:
    int customerID;
    int creditScore;
    short age;
    short tenure;
    double balance;
    bool isActiveMember;

public:
    // Constructors
    Account(int id = 0, int score = 0, short a = 0, short t = 0,
        double b = 0.0, bool active = false)
        : customerID(id), creditScore(score), age(a),
        tenure(t), balance(b), isActiveMember(active) {}

    Account(const QString& csvLine) {
        QStringList fields = csvLine.split(',');
        if (fields.size() >= 6) {
            customerID = fields[0].toInt();
            creditScore = fields[1].toInt();
            age = (short)(fields[2].trimmed().toDouble());
            tenure = fields[3].trimmed().toShort();
            balance = fields[4].trimmed().toDouble();

            QString activeStr = fields[5].trimmed();
            double activeVal = activeStr.toDouble(); 

            isActiveMember = (activeVal == 1.0 || activeStr.toLower() == "true");
        }
    }

    // Getter and Setter for customerID
    int getCustomerID() const {
        return customerID;
    }
    
    void setCustomerID(int id) {
        customerID = id;
    }

    // Getter and Setter for creditScore
    int getCreditScore() const {
        return creditScore;
    }

    void setCreditScore(int score) {
        creditScore = score;
    }

    // Getter and Setter for age
    short getAge() const {
        return age;
    }

    void setAge(short a) {
        age = a;
    }

    // Getter and Setter for tenure
    short getTenure() const {
        return tenure;
    }

    void setTenure(short t) {
        tenure = t;
    }

    // Getter and Setter for balance
    double getBalance() const {
        return balance;
    }

    void setBalance(double b) {
        balance = b;
    }

    // Getter and Setter for isActiveMember
    bool isActive() const {
        return isActiveMember;
    }

    void setActive(bool active) {
        isActiveMember = active;
    }

    // Overload comparison operators for splay tree operations
    bool operator<(const Account& other) const {
        return customerID < other.customerID;
    }

    bool operator>(const Account& other) const {
        return customerID > other.customerID;
    }

    bool operator==(const Account& other) const {
        return customerID == other.customerID;
    }


    // Friend function for output
    //friend std::ostream& operator<<(std::ostream& os, const Account& account) {
    //    os << "Customer ID: " << account.customerID
    //        << "\nCredit Score: " << account.creditScore
    //        << "\nAge: " << account.age
    //        << "\nTenure: " << account.tenure << " years"
    //        << "\nBalance: $" << account.balance
    //        << "\nActive Member: " << (account.isActiveMember ? "Yes" : "No");
    //    return os;
    //}
};


