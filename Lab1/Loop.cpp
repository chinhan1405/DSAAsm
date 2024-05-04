#include<iostream>

using namespace std;

int fibo(int n) {
    if(n == 0 || n == 1) {
        return n;
    }
    return fibo(n-1) + fibo(n-2);

}

class A {
    public:
    int a;
    A(int n) {
        a = n;
    }
    virtual void print() {
        cout << "A" << endl;
    }
};

class B {
    public:
    int b;
    B(A a) {
        b = a.a;
    }
};

class C : public A {
    public:
    int c;
    C(int n) : A(0) {
        c = n;
    }
    void print() {
        cout << "C" << endl;
    }
    
};

int main() {
    C ce(5);
    A* an = &ce;
    an->print();
    return 0;
}
