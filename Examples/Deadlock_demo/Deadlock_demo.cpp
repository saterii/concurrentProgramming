

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex m1;

void processData(vector<int>& data)
{
    if (m1.try_lock())
    {
        data.push_back(rand() % 1000);
        if (data.size() > 500)
        {
            data.erase(data.begin());
        }
        m1.unlock();
    }
    
}

void threadFunc(vector<int>& data)
{
    while (1)
    {
        processData(data);
    }
}

int main()
{
    vector<int> data;
    thread t1(threadFunc, ref(data));
    while (1)
    {
        m1.lock();
        for (auto value : data)
        {
            cout << value << ", ";
        }

        processData(data);
        m1.unlock();
        cout << "\n";
    }
    std::cout << "Hello World!\n";
}

