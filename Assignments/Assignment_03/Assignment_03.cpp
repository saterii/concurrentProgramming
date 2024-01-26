#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex m1;

void addNumber(vector<int>& nums)
{
    while (1)
    {
        m1.lock();
        nums.push_back(rand());
        cout << "Added a number!\n";
        m1.unlock();
    }
}

void removeNumber(vector<int>& nums)
{
    while (1)
    {
        if (!nums.empty())
        {
            m1.lock();
            nums.erase(nums.begin());
            cout << "Removed a number!\n";
            m1.unlock();
        }
    }
}

int main()
{
    vector<int> numbers;
    thread t1(addNumber, ref(numbers));
    thread t2(removeNumber, ref(numbers));
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    cout << "Hello World!\n";
}
