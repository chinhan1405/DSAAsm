#include <iostream>
using namespace std;

template <class T>
class DLinkedList 
{
public:
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() ;
    ~DLinkedList();
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
};

template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
};

template<class T>
void push(T item) {
    // TODO: Push new element into the top of the stack
    list.add(item);
}

template<class T>
T pop() {
    // TODO: Remove an element on top of the stack
    list.removeAt(list.size()-1);
}

template<class T>
T top() {
    // TODO: Get value of the element on top of the stack
    return list.get(list.size()-1);
}

template<class T>
bool empty() {
    // TODO: Determine if the stack is empty
    return list.empty();
}

template<class T>
int size() {
    // TODO: Get the size of the stack
    return list.size();
}

template<class T>
void clear() {
    // TODO: Clear all elements of the stack
    list.clear();
}