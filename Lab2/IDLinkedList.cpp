#include <iostream>
using namespace std;

template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString() {
        string result = "[";
        Node *temp = this->head;
        while (temp != nullptr)
        {
            result += to_string(temp->data) + " ";
            temp = temp->next;
        }
        return result + "]";
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        
        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

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
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};


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
    Node *temp = this->head;
    for (int i = 0; i < this->count; i++)
    {
        if (temp->data == item)
        {
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
            delete temp;
            this->count--;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (this->head != nullptr)
    {
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->tail = nullptr;
    this->count = 0;
}

template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) 
{
    this->pList = pList;
    if (begin)
    {
        this->current = pList->head;
        this->index = 0;
    }
    else
    {
        this->current = nullptr;
        this->index = pList->count;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->pList = iterator.pList;
    this->current = iterator.current;
    this->index = iterator.index;
    return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (this->current != nullptr) this->current->data = e;
    pList->add(index, e);
    current = pList->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() 
{
    return this->current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() 
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current == nullptr)
    {
        return;
    }
    current = current->previous;
    pList->removeAt(index--);
    
    
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) 
{
    return !(this->pList==iterator.pList && this->index==iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() 
{
    Iterator& temp = *this;
    if (this->current == nullptr)
    {
        this->current = this->pList->head;
        this->index = 0;
    }
    else {
        this->current = this->current->next;
        this->index++;
    }
    return temp;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) 
{
    if (this->current == nullptr)
    {
        this->current = this->pList->head;
        this->index = 0;
    }
    else {
        this->current = this->current->next;
        this->index++;
    }    
    return *this;
}


int main() {
    DLinkedList<int> list;
    // int size = 10;
    // for (int idx = 0; idx < size; idx++)
    // {
    //     list.add(idx);
    // }

    DLinkedList<int>::Iterator it = list.begin();
    for (int i = 0; i < 10; i++)
    {
        it.set(i);
        it++;
    }
    
    cout << endl << list.toString();
}