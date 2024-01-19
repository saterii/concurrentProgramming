#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

class DataContainer
{
public:
    DataContainer() : number(0)
    {

    }
    void increment()
    {
        m.lock(); // use mutex lock for synchronization
        ++number;
        m.unlock();
    }
    int number;
    mutex m;
};

void threadFunction(DataContainer& data)
{
    for (int i = 0; i < 100000; ++i)
    {
        data.increment();
    }
}

int main()
{
    DataContainer data;
    thread t1(threadFunction, ref(data));
    thread t2(threadFunction, ref(data));
    t1.join();
    t2.join();

    std::cout << "Threads done, result=" << data.number << "\n";
}
