#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList()
    {
      this->head = nullptr;
      this->tail = nullptr;
      this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort() {
        if (!head) {
            printList();
            return;
        }
        if (!head->next) {
            printList();
            return;
        }
        for (int i=0; i<size()-1; i++) {
            int counter = 0;
            Node *iter = head;
            while (iter->next) {
                if (iter->data > iter->next->data) {
                    counter++;
                    T temp = iter->data;
                    iter->data = iter->next->data;
                    iter->next->data = temp;
                }
                iter = iter->next;
            }
            if (counter == 0) {
                counter = 0;
                continue;
            }
            printList();
        }
    }
};

int main() {
    int arr[] = {1, 2, 5, 2, 3, 0, 0, 0, 0};
    SLinkedList<int> list;
    for(int i = 0; i <int(sizeof(arr))/4;i++)
        list.add(arr[i]);
    list.bubbleSort();
}