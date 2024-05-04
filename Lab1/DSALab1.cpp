// DSALab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


void printArray(int n) {
    if (n == 0) cout << n;
    else {
        printArray(n - 1);
        cout << ", " << n;
    }
}

void printPattern(int n) {
    if (n <= 0) cout << n;
    else {
        cout << n << " ";
        printPattern(n - 5);
        cout << " " << n;
    }
}

int findMax(int* arr, int length)
{
    if (length == 1) return arr[0];
    else {
        int first = arr[length - 1];
        int second = findMax(arr, length - 1);
        if (first > second) return first;
        else return second;
    }
}

string trim(string str) {
    if (str[0] == ' ') return trim(str.substr(1, str.length() - 1));
    else if (str[str.length() - 1] == ' ') return trim(str.substr(0, str.length() - 1));
    else return str;
}

template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    ArrayList() { capacity = 5; count = 0; data = new T[5]; }
    ~ArrayList() { delete[] data; }
    void    add(T e);
    void    add(int index, T e);
    int     size();
    void    ensureCapacity(int index);
};

template<class T>
void ArrayList<T>::ensureCapacity(int cap) {
    /*
        if cap > capacity:
            new_capacity = capacity * 1.5;
            create new array with new_capacity
        else: do nothing
    */
    if (cap > capacity) {
        capacity = capacity * 1.5;
        T* new_data = new T[capacity];
        for (int i = 0; i < count; i++) {
            new_data[i] = data[i];
        }
        delete data;
        data = new_data;
    }
}

template <class T>
void ArrayList<T>::add(T e) {
    /* Insert an element into the end of the array. */
    ensureCapacity(count++);
    data[count - 1] = e;
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
    ensureCapacity(count++);
    for (int i = count - 1; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;

}

template<class T>
int ArrayList<T>::size() {
    /* Return the length (size) of the array */
    return count;
}


bool isPalindrome(string str)
{
    if (str.length() <= 1) return true;
    else {
        string new_string = str.substr(1, str.length() - 2);
        return (str[0] == str[str.length() - 1]) && isPalindrome(trim(new_string));
    }
    cout<<sqrt(12);
}


vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    // STUDENT ANSWER
    for (int i = 0; i < operations.size(); i++) {
        for (int j = operations[i][0]; j <= operations[i][1]; j++) {
            nums[j] += operations[i][2];
        }
    }
    return nums;
}


void printVector(vector<int> vt) {
    for (int i = 0; i < vt.size(); i++) {
        cout << vt[i] << " ";
    }
}

int findGCD(int a, int b)
{
    if (a == b) return a;
    else if (a < b) return findGCD(a, b - a);
    else return findGCD(a - b, b);
}



//int toDigit(char n) {
//    if (n > 47 && n < 58) return n - 48;
//    else if (n == '(' || n == ')') return -2;
//    else return -1;
//}

//string loopString(string str, int t) {
//    if (t == 0) return "";
//    if (t == 1) return str;
//    else return str + loopString(str, t - 1);
//}
//
//string expand(string s) {
//    size_t stop = s.find_first_of(')');
//    if (stop == string::npos) return s;
//    size_t start = s.find_last_of('(', stop);
//    string new_string = loopString(s.substr(start + 1, stop - start - 1), toDigit(s[start - 1]));
//    return expand(s.replace(start - 1, stop - start + 2, new_string));
//}

void printHailstone(int number)
{
    cout << number << " ";
    if (number == 2) cout << 1;
    else if (number % 2 == 0) printHailstone(number / 2);
    else printHailstone(number * 3 + 1);
}

int pow10(int n) {
    if (n == 0) return 1;
    return 10 * pow10(n - 1);
}

int toDigit(char n) {
    if (n > 47 && n < 58) return n - 48;
    else return -1;
}

int myArrayToInt(char* str, int n)
{
    if (n == 0) return 0;
    return toDigit(str[n-1]) + 10*myArrayToInt(str, n-1);
}

int strlen_(char* str, int index) {
    if (str[index] == '\0') return index;
    else return strlen_(str, index++);
}


int strLen(char* str)
{
    return strlen_(str, 0);
}

string getFirstWord(string s) {
    if (s.length() == 0) return "";
    if (s[0] == ' ') return "";
    return s[0] + getFirstWord(s.substr(1));
}

string reverseSentence(string s) {
    string fword = getFirstWord(s);
    size_t wordLen = fword.length();
    if (s.length()==wordLen) return fword;
    return reverseSentence(s.substr(wordLen+1)) + " " + fword;
}

int bracketAddGroup(string s, int index) {
    if (s[index] == ')') return -1;
    else return 1 + bracketAddGroup(s, index + 1);
}

int mininumBracketAdd_(string &s, int start, int closeBracketWaitingCount) {
    if (s.length() == 0) return 0;
    if (s.length() == 1) return 1;
    if (((int)s.length() - 1) == start) {
        if (closeBracketWaitingCount == 0) return 1;
        else if (s[start] == '(') return 1 + closeBracketWaitingCount;
        else return closeBracketWaitingCount - 1;
    }
    if (closeBracketWaitingCount == 0) {
        if (s[start] == ')') return mininumBracketAdd_(s, start + 1, closeBracketWaitingCount) + 1;
        else return mininumBracketAdd_(s, start + 1, closeBracketWaitingCount + 1);
    }
    else {
        if (s[start] == ')') return mininumBracketAdd_(s, start + 1, closeBracketWaitingCount - 1);
        else return mininumBracketAdd_(s, start + 1, closeBracketWaitingCount + 1);
    }
    
}

int mininumBracketAdd(string s) {
    
    return mininumBracketAdd_(s, 0, 0);
}

enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price)
    {
        this->price = price;
        this->color = color;
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        /*
         * STUDENT ANSWER
         */
         this->price = price;
         this->size = size;
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
        this->numberOfItems = 0;
        toyBox[0] = nullptr;
    }
    
    int addItem(const CarToy& carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
        if (this->numberOfItems == 5) return -1;
        else {
            CarToy* newCar = new CarToy(carToy.price, carToy.color);
            this->toyBox[numberOfItems] = newCar;
        }
        return 0;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
        if (this->numberOfItems == 5) return -1;
        else {
            PuzzleToy* newPuzzle = new PuzzleToy(puzzleToy.price, puzzleToy.size);
            this->toyBox[numberOfItems] = newPuzzle;
        }
        return 0;
    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};



int main()
{
    CarToy car(20000,red);
    PuzzleToy puzzle(30000,small);
    car.printType();
    puzzle.printType();
}
