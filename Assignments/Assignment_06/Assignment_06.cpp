#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <string>
#include <atomic>

using namespace std;

class BankAccount {
public:
    BankAccount(string name) { AccountName = name; }
    string AccountName;
    void Deposit(double amount) {
        
        balance.operator=(balance + amount);
        operationCount++;
        CheckInterest();
    }
    void Withdraw(double amount) {
        if (amount <= balance) {
            balance.operator=(balance - amount);
            operationCount++;
            CheckInterest();
        }
    }

    double GetBalance() const { return balance; }

    int GetOperations() { return operationCount; }

private:
    std::atomic<double> balance = 0;
    std::atomic<int> operationCount = 0;

    void CheckInterest() {
        if (operationCount % 100 == 0) {
            AddInterest();
            cout << "\n\nAdded interest!\n\n";
        }
    }

    void AddInterest()
    {
        balance = balance * 1.0005;
    }
};

mutex m1;

void DepositRandom(BankAccount& accA, BankAccount& accB) {
    while (true) {
        double amount = ceil(rand() % 500 + 500 * pow(10.0, 2)) / pow(10.0, 2);
        if (accA.GetBalance() >= amount) {
            accA.Withdraw(amount);
            accB.Deposit(amount);
            cout << "Transferred " + to_string(amount) + "e from account " + accA.AccountName + " to account " + accB.AccountName + "\n";
            cout << "Account A balance: " + to_string(accA.GetBalance()) + "e\n";
            cout << "Account B balance: " + to_string(accB.GetBalance()) + "e\n";
        }
    }
}

int main() {
    BankAccount acc1("A");
    BankAccount acc2("B");
    acc1.Deposit(1000);
    acc2.Deposit(1000);

    thread t1(DepositRandom, ref(acc1), ref(acc2));
    thread t2(DepositRandom, ref(acc1), ref(acc2));
    thread t3(DepositRandom, ref(acc2), ref(acc1));
    thread t4(DepositRandom, ref(acc2), ref(acc1));

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();
    if (t3.joinable()) t3.join();
    if (t4.joinable()) t4.join();

    return 0;
}

