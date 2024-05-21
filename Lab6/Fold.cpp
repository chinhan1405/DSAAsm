#include <iostream>

using namespace std;

int powerof10(int n) {
    int ret = 1;
    for (int i=0; i<n; i++) {
        ret *= 10;
    }
    return ret;
}

int foldShift(long long key, int addressSize) {
    long long upper = 1;
    while (key > upper) { 
        upper *= 10;  
    }
    int step = powerof10(addressSize);
    int res = 0;
    while (key > step) {
        upper /= step;
        res += key / upper;
        key %= upper;
    }
    res += key;
    return res % step;
}

int rotation(long long key, int addressSize) {
    long long last = key % 10;
    key /= 10;
    long long temp = key;
    while (temp > 0) {
        last *= 10;
        temp /= 10;
    }
    return foldShift(last+key, addressSize);
}

int main() {
    cout << rotation(600101, 2) << endl;
    cout << foldShift(600101, 2) << endl;
    cout << foldShift(1234567892, 3) << endl;
}