#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

void cpu_waster()
{
    cout << "cpu_waster process id: " << _getpid() << "\n";
    cout << "cpu_waster thread id: " << this_thread::get_id() << "\n";
    while (true)
    {
        // waste cpu cycles

    }
}

int main()
{
    cout << "main process id: " << _getpid() << "\n";
    cout << "main thread id: " << this_thread::get_id() << "\n";
    
    vector<thread> threads;
    for (size_t i = 0; i < 2; ++i)
    {
        threads.push_back(thread(cpu_waster));
    }
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Running\n";
    }
}
