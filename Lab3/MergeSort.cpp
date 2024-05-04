#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    static void merge(T* left, T* middle, T* right){
        T* temp = new T[right - left + 1];
        T* l = left;
        T* m = middle;
        for (int i = 0; i < right - left + 1; i++) {
            if (l == middle) {
                temp[i] = *m;
                m++;
            }
            else if (m == right + 1) {
                temp[i] = *l;
                l++;
            }
            else if (*l < *m) {
                temp[i] = *l;
                l++;
            }
            else {
                temp[i] = *m;
                m++;
            }
        }
        for (int i = 0; i < right - left + 1; i++) {
            left[i] = temp[i];
        }
        Sorting::printArray(left, right);
    }
    static void mergeSort(T* start, T* end) {
        if (start >= end) return;
        T* middle = start + (end - start) / 2;
        mergeSort(start, middle);
        mergeSort(middle + 1, end);
        merge(start, middle + 1, end);
    }
};

int main() {
    int arr[] = {0,2,4,3,1,4};
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
}