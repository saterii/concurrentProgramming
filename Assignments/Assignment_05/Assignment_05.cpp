#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m1;
condition_variable c1;
bool dataReady = false;

void setDataReady()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4000 + 1000));
    {
        lock_guard<mutex> guard(m1);
        dataReady = true;
    }
        c1.notify_one();
}

void checkIfDataReady()
{
        unique_lock<mutex> lock(m1);
        cout << "Waiting for data...\n";
        c1.wait(lock, [] {return dataReady; });
        dataReady = false;
        cout << "Data is ready!\n";
}

int main()
{
    thread t1([] {while (1) { setDataReady(); }});
    thread t2([] {while (1) { checkIfDataReady(); }});
    t2.join();
    t1.join();

    return false;
}

