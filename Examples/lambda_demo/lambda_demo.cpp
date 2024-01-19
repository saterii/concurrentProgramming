
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    thread t1([]
        {
            cout << "Thread executing lambda \n";
        });
    t1.join();
    std::cout << "All done\n";
}
