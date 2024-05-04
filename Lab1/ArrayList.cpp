#include <iostream>
using namespace std;

template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    ArrayList(){capacity = 5; count = 0; data = new T[5];}
    ~ArrayList(){ delete[] data; }
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item);
    bool    contains(T item);
    T       removeAt(int index);
    bool    removeItem(T item);
    void    ensureCapacity(int index);
    string toString() {
        string s = "";
        for (int i = 0; i < count; i++) {
            s += to_string(data[i]);
            if (i < count - 1) s += ", ";
        }
        return s;
    }
};

template<class T>
void ArrayList<T>::ensureCapacity(int cap){
    /* 
        if cap > capacity: 
            new_capacity = capacity * 1.5;
            create new array with new_capacity
        else: do nothing
    */
    if (cap > capacity) {
        capacity = capacity * 1.5;
        T* new_data = new T[capacity];
        for (int i=0; i<count; i++) {
            new_data[i] = data[i];
        }
        delete [] data;
        data = new_data;
    }
}

template <class T>
void ArrayList<T>::add(T e) {
    /* Insert an element into the end of the array. */
    ensureCapacity(++count);
    data[count-1] = e;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
    /* 
        Insert an element into the array at given index.
        if index is invalid:
            throw std::out_of_range("the input index is out of range!");
    */ 
    if (index < 0 || index > count)
        throw std::out_of_range("the input index is out of range!");
    ensureCapacity(++count);
    for (int i=count-1; i>index; i--) {
        data[i] = data[i-1];
    }
    data[index] = e;
    
}

template<class T>
int ArrayList<T>::size() {
    /* Return the length (size) of the array */ 
    return count;
}

template<class T>
T ArrayList<T>::removeAt(int index){
    /*
    Remove element at index and return removed value 
    if index is invalid:
        throw std::out_of_range("index is out of range");
    */
    if (index < 0 || index >= count)
        throw std::out_of_range("index is out of range");
    T removed = data[index];
    for (int i=index; i<count-1; i++) {
        data[i] = data[i+1];
    }
    count--;
    return removed;
}

template<class T>
bool ArrayList<T>::removeItem(T item){
     /* Remove the first apperance of item in array and return true, otherwise return false */
    for (int i=0; i<count; i++) {
        if (data[i] == item) {
            removeAt(i);
            return true;
        }
    }
}

template<class T>
void ArrayList<T>::clear(){
    /* 
        Delete array if array is not NULL
        Create new array with: size = 0, capacity = 5
    */
    if (data != NULL) {
        delete [] data;
        data = new T[5];
        capacity = 5;
        count = 0;
    }
}

int main() {
        ArrayList<int> arr;

    for (int i = 0; i < 10; ++i) {
        arr.add(i);
    }
    arr.removeAt(9);

    cout << arr.toString() << '\n';
    cout << arr.size();
}