#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void looper(int threadNumber)
{
    for (int i = 0; i < 1000; ++i) {
        cout << "Current loop value for thread " << threadNumber << ": " << i << "\n";
    }
}
int main()
{
    const auto processors = std::thread::hardware_concurrency(); // find the amount of logical processors
    vector<thread> threads;
    for (int i = 0; i < processors; ++i)
    {
        threads.push_back(thread(looper, i + 1));
    }
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
    std::cout << "All tasks done";
}
