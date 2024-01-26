#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void print()
{
    cout << "Critical data\n";
}



int main()
{
    mutex m1, m2;
    thread t1([&m1, &m2]
        {
            cout << "Acquiring first mutex...\n";
            m1.lock();
            print();

            cout << "Acquiring second mutex...\n";
            m2.lock();
            print();

            m1.unlock();
            m2.unlock();
        });

    thread t2([&m1, &m2]
        {
            cout << "Acquiring second mutex...\n";
            m2.lock();
            print();

            cout << "Acquiring first mutex...\n";
            m1.lock();
            print();

            m2.unlock();
            m1.unlock();
            
        });

    t1.join();
    t2.join();

    cout << "All done!\n";
}

