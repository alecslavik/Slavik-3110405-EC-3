#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account {
public:
    Account(string accountNumber, string accountHolder, double balance) :
        accountNumber(accountNumber), accountHolder(accountHolder), balance(balance) {}

    virtual void displayDetails() const {
        cout << "Account Details for Generic Account (ID: " << accountNumber << "):" << endl;
        cout << "   Holder: " << accountHolder << endl;
        cout << "   Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        }
    }

    double getBalance() const {
        return balance;
    }

protected:
    string accountNumber;
    string accountHolder;
    double balance;
};

class SavingsAccount : public Account {
public:
    SavingsAccount(string accountNumber, string accountHolder, double balance, double interestRate) :
        Account(accountNumber, accountHolder, balance), interestRate(interestRate) {}

    void displayDetails() const override {
        cout << "Account Details for Savings Account (ID: " << accountNumber << "):" << endl;
        cout << "   Holder: " << accountHolder << endl;
        cout << "   Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "   Interest Rate: " << fixed << setprecision(2) << interestRate * 100 << "%"<< endl;
    }

    void withdraw(double amount) override {
        if (balance - amount >= 1000) {
            balance -= amount;
        }
    }

private:
    double interestRate;
};

class CurrentAccount : public Account {
public:
    CurrentAccount(string accountNumber, string accountHolder, double balance, double overdraftLimit) :
        Account(accountNumber, accountHolder, balance), overdraftLimit(overdraftLimit) {}

    void displayDetails() const override {
        cout << "Account Details for Current Account (ID: " << accountNumber << "):" << endl;
        cout << "   Holder: " << accountHolder << endl;
        cout << "   Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "   Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << endl;
    }

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
        }
    }

private:
    double overdraftLimit;
};

CurrentAccount operator+(CurrentAccount current, SavingsAccount savings) {
    double amount = 300;
    if (savings.getBalance() >= amount) {
        savings.withdraw(amount);
        current.deposit(amount);
    }

    cout << "Account Details after transfer:" << endl;
    savings.displayDetails();
    cout << endl;
    current.displayDetails();
    cout << endl;

    return current;
}

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    cout << endl;
    current.displayDetails();
    cout << endl;

    savings.deposit(500);
    current.withdraw(1000);

    cout << "Account Details after deposit and withdrawal:" << endl;
    savings.displayDetails();
    cout << endl;
    current.displayDetails();
    cout << endl;

    // Transfer 300 from savings to current
    current = current + savings;

    return 0;
}