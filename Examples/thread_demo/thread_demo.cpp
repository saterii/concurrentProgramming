#include <iostream>
#include<thread>
using namespace std;

void runningNumber(int count, const string& msg)
{
    cout << "runningNumber: entering\n";
    const auto id = this_thread::get_id();
    for (int i = 0; i < count; ++i)
    {
        cout << "runningNumber: thread id: " << id;
        cout << " " << msg << ", i=" << i << "\n";

    }
    cout << "runningNumber: leaving\n";
}

void increaseNumber(int& number, int count)
{
    while (--count)
    {
        ++number;
        cout << "increaseNumber: " << number << "\n";
    }
}

int main()
{
    // create thread
    thread t1(runningNumber, 100, "Hello from main");
    cout << "main: started thread t1\n";

    if (t1.joinable())
        t1.join();

    int number = 0;
    thread t2(increaseNumber, ref(number), 100);
    cout << "main: started thread t2\n";

    if (t2.joinable())
        t2.join();

    cout << "main: exiting\n";
    cout << "number: " << number;
}
