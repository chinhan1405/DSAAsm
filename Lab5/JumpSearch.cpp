#include <iostream>
#include <cmath>
using namespace std;

int jumpSearch(int arr[], int x, int n) {
    int step = sqrt(n);
    int cur = 0;
    if (arr[cur] == x) {
        cout << cur << " ";
        return cur;
    }
    while (cur < n && arr[cur] <= x) {
        cout << cur << " ";
        cur += step;
        if (arr[cur] == x) {
            cout << cur << " ";
            return cur;
        }
    }
    if (cur <= n) cout << cur << " ";
    for (int i = cur - step + 1; i < cur; i++) {
        if (arr[i] > x) {
            return -1;
        }
        cout << i << " ";
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
}