#include<iostream>
#include<list>
using namespace std;

class DataLog
{
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog();
    DataLog(const int &data);
    void addCurrentState(int number);
    void subtractCurrentState(int number);
    void save();
    void undo();
    void redo();

    int getCurrentStateData()
    {
        return *currentState;
    }
    
    void printLog()
    {      
        for (auto i = logList.begin(); i != logList.end(); i++) {
            if(i == currentState) cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};


DataLog::DataLog()
{
    currentState = logList.begin();
}

DataLog::DataLog(const int &data)
{
    currentState = logList.begin();
    logList.push_back(data);
    currentState++;
}

void DataLog::addCurrentState(int number)
{
    *currentState += number;
}

void DataLog::subtractCurrentState(int number)
{
    *currentState -= number;
}

void DataLog::save()
{
    int value = *currentState;
    list<int>::iterator temp = logList.end();
    temp--;
    while(temp != currentState)
    {
        temp--;
        logList.pop_back();
    }
    logList.push_back(value);
    currentState++;
}

void DataLog::undo()
{
    if (currentState != logList.begin())
    {
        currentState--;
    }
}

void DataLog::redo()
{
    currentState++;
    if (currentState == logList.end())
    {
        currentState--;
    }
}

int main() {
    DataLog log(10);
log.save();
log.addCurrentState(15);
log.save();
log.addCurrentState(15);
log.save();
log.undo();
log.undo();
log.printLog();
cout << "\n";
log.save();
log.printLog();
    return 0;
}

