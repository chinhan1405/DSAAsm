#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class PrinterQueue
{
    map<int, queue<string>> requests;

    void pushRequest(int priority, string fileName)
    {
        priority = -priority;
        if (requests.size() == 0 || requests.find(priority) == requests.end()) {
            requests[priority] = queue<string>();
            requests[priority].push(fileName);
            return;
        }
        requests[priority].push(fileName);
    }

    string popRequest()
    {
        if (requests.size() == 0) {
            return "No file to print";
        }
        if (requests.begin()->second.size() == 0) {
            requests.erase(requests.begin());
            return popRequest();
        }
        string fileName = requests.begin()->second.front();
        requests.begin()->second.pop();
        return fileName;
    }
public:
    // your methods

    void addNewRequest(int priority, string fileName)
    {
        pushRequest(priority, fileName);
    }

    void print()
    {
        cout << popRequest() << endl;
    }
};

int main()
{
    PrinterQueue* myPrinterQueue = new PrinterQueue();
    myPrinterQueue->addNewRequest(1, "hello.pdf");
    myPrinterQueue->addNewRequest(2, "goodbye.pdf");
    myPrinterQueue->addNewRequest(2, "goodnight.pdf");
    myPrinterQueue->addNewRequest(2, "goodluck.pdf");
    myPrinterQueue->addNewRequest(3, "goodmorning.pdf");
    myPrinterQueue->addNewRequest(3, "goodafternoon.pdf");
    myPrinterQueue->addNewRequest(3, "goodevening.pdf");

    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
}