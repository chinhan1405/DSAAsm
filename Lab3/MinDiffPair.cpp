#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string minDiffPairs(int* arr, int n) {
    sort(arr, arr+n);
    int minDiff = arr[1] - arr[0];
    for (int i=2; i<n; i++) {
        minDiff = min(minDiff, arr[i] - arr[i-1]);
    }
    stringstream ss;
    int i = 1;
    for (; i<n; i++) {
        if (arr[i] - arr[i-1] == minDiff){
            ss << "(" << arr[i-1] << ", " << arr[i] << ")";
            i++;
            break;
        }
    }
    for (; i<n; i++) {
        if (arr[i] - arr[i-1] == minDiff){
            ss << ", (" << arr[i-1] << ", " << arr[i] << ")";
        }
    }
    return ss.str();
}

int main() {
    int arr[] = {10, 5, 7, 9, 15, 6, 11, 8, 12, 2};
    cout << minDiffPairs(arr, 10);
}