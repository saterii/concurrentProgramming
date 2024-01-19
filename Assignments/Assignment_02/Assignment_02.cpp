#include <iostream>
#include <thread>

using namespace std;

void setElements(int* arr1, int size)
{
    cout << "Entering thread..\n";
    for (int i = 0; i < size; ++i)
    {
        arr1[i] = rand() % 1000;
    }
    cout << "Exiting thread..\n";
}

int main()
{
    cout << "Entering main..\n";
    int number;
    cout << "Enter amount of numbers to allocate: ";
    cin >> number;
    int* numbers = new int[number];
    thread t1(setElements, numbers, number);
    t1.join();
    for (int i = 0; i < number; ++i)
    {
        cout << numbers[i] << " ";
    }
    cout << "\nExiting main..\n";
}
