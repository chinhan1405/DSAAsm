#include <iostream>

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
    SLinkedList() {
        head = 0;
        tail = 0;
        count = 0;
    };
    ~SLinkedList() {
        delete head;
        delete tail;
    }
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    T       get(int index);
    void    set(int index, const T& e);
    bool    empty();
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
    void    clear();

    string  toString() {
        string output = "";
        Node* current = head;
        while (current != 0) {
            output += to_string(current->data) + " ";
            current = current->next;
        }
        return output;
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
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if (head == 0) {
        head = new Node(e, 0);
        tail = head;
    } else {
        tail->next = new Node(e, 0);
        tail = tail->next;
    }
    count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    count++;
    if (index == 0) {
        head = new Node(e, head);
        if (tail == 0) tail = head;
        return;
    }
    Node* prev = head;
    for (int i=0; i<index-1; i++) {
        prev = prev->next;
    }
    prev->next = new Node(e, prev->next);
    if (prev == tail) tail = prev->next;
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}

template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= count) return 0;
    Node* current = head;
    for (int i=0; i<index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index >= 0 && index < count) {
        Node* current = head;
        for (int i=0; i<index; i++) {
            current = current->next;
        }
        current->data = e;
    }
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (count == 0);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* current = head;
    for (int i=0; i<count; i++) {
        if (current->data == item) return i;
        current = current->next;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node* current = head;
    for (int i=0; i<count; i++) {
        if (current->data == item) return true;
        current = current->next;
    }
    return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count) return 0;
    count--;
    if (index == 0) {
        T data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }
    Node* prev = head;
    for (int i=0; i<index-1; i++) {
        prev = prev->next;
    }
    T data = prev->next->data;
    if (prev->next == tail) tail = prev;
    Node* temp = prev->next;
    prev->next = prev->next->next;
    delete temp;
    return data;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node* current = head;
    if (current->data == item) {
        head = head->next;
        delete current;
        count--;
        return true;
    }
    for (int i=0; i<count-1; i++) {
        if (current->next->data == item) {
            if (current->next == tail) tail = current;
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (head != 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = 0;
    count = 0;
}




int main(int argc, char const *argv[])
{ 	
    SLinkedList<int> list;

    for (int i = 0; i < 10; ++i) {
        list.add(i);
    }
    cout << (list.get(0) == list.removeAt(0)) << endl;

    cout << list.toString();
}
