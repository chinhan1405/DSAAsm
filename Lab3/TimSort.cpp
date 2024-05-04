#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int  size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* start, T* middle, T* end) {
        if (start >= end) return;
        if (middle > end) return;
        T* temp = new T[end - start];
        T* l = start;
        T* m = middle;
        for (int i = 0; i < end - start; i++) {
            if (l == middle) {
                temp[i] = *m;
                m++;
            }
            else if (m == end) {
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
        for (int i = 0; i < end - start; i++) {
            start[i] = temp[i];
        }
        delete[] temp;
    }
public:
    static void InsertionSort(T* start, T* end) {
        if (start>=end) return;
        for (T* i=start; i<end-1; i++) {
            T* max = i;
            for (T* j=i+1; j<=end-1; j++) {
                if (*j < *max) {
                    max = j;
                }
            }
            T temp = *max;
            *max = *i;
            *i = temp;
        }
    }

    static void TimSort(T* start, T* end, int min_size) {
        int size = end - start;
        for (T* i = start; i < end; i += min_size) {
            T* right = i + min_size;
            if (right > end) right = end;
            InsertionSort(i, right);
        }
        cout << "Insertion Sort: ";
        printArray(start, end);
        int count = 0;
        for (int i = min_size; i < size; i *= 2) {
            for (T* j = start; j < end; j += 2 * i) {
                T* middle = j + i;
                T* right = j + 2 * i;
                if (right > end) right = end;
                merge(j, middle, right);
                cout << "Merge " << ++count << ": ";
                printArray(start, end);
            }
        }

    }
};


int main() {
    int array[] = { 1, 2, 3, 4 };
    int min_size = 3;
    Sorting<int>::TimSort(&array[0], &array[sizeof(array)/4], min_size);
}