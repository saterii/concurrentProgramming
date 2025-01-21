#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

class BankAccount {
public:
    BankAccount(string name) { AccountName = name; }
    string AccountName;
    void Deposit(int amount) {
        balance += amount;
    }
    void Withdraw(int amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }
    int GetBalance() const { return balance; }

private:
    int balance = 0;
};

mutex m1;

void DepositRandom(BankAccount& accA, BankAccount& accB) {
    while (true) {
        int amount = rand() % 500 + 500;
        if (accA.GetBalance() >= amount) {
            if (m1.try_lock()) {
                accA.Withdraw(amount);
                accB.Deposit(amount);
                cout << "Transferred " + to_string(amount) + "e from account " + accA.AccountName + " to account " + accB.AccountName + "\n";
                cout << "Account A balance: " + to_string(accA.GetBalance()) + "e\n";
                cout << "Account B balance: " + to_string(accB.GetBalance()) + "e\n";
                m1.unlock();
            }
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

