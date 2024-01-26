#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <functional> // std::bind


using namespace std;

class Application
{
public:
    Application() : m_dataLoaded(false)
    {

    }

    bool isDataLoaded() const { return m_dataLoaded; }

    void waitForLoadData()
    {
        // acquire mutex lock
        unique_lock<mutex> mlock(m_mutex);

        m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
    }

    void loadData()
    {
        lock_guard<mutex> guard(m_mutex);

        srand((unsigned int)time(0));

        // simulate work

        for (int i = 0; i <= 100; i += 10)
        {
            for (int j = 0; j < 50; ++j)
            {
                m_data.push_back((char)(rand() % 64 + 33));
            }
            this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
            cout << "Loading data " << i << "%\n";
        }
        m_dataLoaded = true;

        m_condVar.notify_one();
    }

    void connectToServer()
    {
        // simulate connecting

        cout << "Connecting to server...\n";
        for (int i = 0; i <= 100; i += 25)
        {
            this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
            cout << "Handshaking with server " << i << "%\n";
        }
        cout << "Connected to server!\n";
        waitForLoadData();
    }

    void uploadData()
    {
        // simulate uploading

        cout << "Uploading data...\n";
        for (auto data : m_data)
        {
            cout << data << ",";
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\nUpload complete!\n";
    }

private:
    mutex                   m_mutex;
    condition_variable      m_condVar;
    bool                    m_dataLoaded;
    vector<char>            m_data;
};

int main()
{
    Application app;
    thread t1(&Application::connectToServer, &app);
    thread t2(&Application::loadData, &app);
    t1.join();
    t2.join();
    
    app.uploadData();
    
    
}
