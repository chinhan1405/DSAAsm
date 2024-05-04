#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;


template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end) {
        int i = 0; 
        int j = end-start;
        int pivot = start[0];
        T temp;
        do {
            do {i++;} while (start[i] < pivot);
            do {j--;} while (start[j] > pivot);
            temp = start[i];
            start[i] = start[j];
            start[j] = temp;
        } while (i<j);
        temp = start[i];
        start[i] = start[j];
        start[j] = temp;
        temp = start[j];
        start[j] = start[0];
        start[0] = temp;
        return &start[j];
    }
public:
    static void QuickSort(T* start, T* end) {
        if (start>=end) return;
        T* pivot = Partition(start, end);
        cout << (pivot-start) << " ";
        QuickSort(start, pivot);
        QuickSort(pivot+1, end);
    }
};

int main() {
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
}