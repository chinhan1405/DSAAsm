#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList();
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
    string  toString() {
        stringstream ss;
        Node* ptr = head;
        while(ptr != nullptr) {
            ss << ptr->data << " ";
            ptr = ptr->next;
        }
        return ss.str();
    
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};

template <class T>
DLinkedList<T>::DLinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
    while (this->head != nullptr)
    {
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
}

template <class T>
void DLinkedList<T>::add(const T& e) {
    Node *newNode = new Node(e);
    if (this->head == nullptr)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        newNode->previous = this->tail;
        this->tail = newNode;
    }
    this->count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    Node *newNode = new Node(e);
    if (index == 0)
    {
        newNode->next = this->head;
        if (this->head) this->head->previous = newNode;
        else this->tail = newNode;
        this->head = newNode;
    }
    else
    {
        Node *temp = this->head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->previous = temp;
        temp->next = newNode;
        if (newNode->next != nullptr)
        {
            newNode->next->previous = newNode;
        }
        else
        {
            this->tail = newNode;
        }
    }
    this->count++;
}

template<class T>
int DLinkedList<T>::size() {
    return this->count;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    Node *temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    Node *temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node *temp = this->head;
    for (int i=0; i < this->count; i++)
    {
        if (temp->data == item)
        {
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node *temp = this->head;
    for (int i=0; i < this->count; i++)
    {
        if (temp->data == item)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= this->count)
    {
        throw "Index out of range";
    }
    Node *temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    if (temp->previous != nullptr)
    {
        temp->previous->next = temp->next;
    }
    else
    {
        this->head = temp->next;
    }
    if (temp->next != nullptr)
    {
        temp->next->previous = temp->previous;
    }
    else
    {
        this->tail = temp->previous;
    }
    T data = temp->data;
    delete temp;
    this->count--;
    return data;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
}




int main() {
    DLinkedList<int> list;
    int size = 10;
    for(int idx=0; idx < size; idx++){
    list.add(idx);
    }
    for(int idx=0; idx < size; idx++){
    cout << list.get(idx) << " |";
    }
    return 0;
}