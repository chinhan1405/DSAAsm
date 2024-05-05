#include <iostream>
using namespace std;
void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    int child;
    while (true) {
        if (index*2 >= numberOfElements-1) return;
        int leftChild = index*2 + 1;
        int rightChild = index*2 + 2;
        if (maxHeap[leftChild] < maxHeap[rightChild]) {
            child = rightChild;
        }
        else {
            child = leftChild;
        }
        if (maxHeap[index] < maxHeap[child]) {
            int temp = maxHeap[index];
            maxHeap[index] = maxHeap[child];
            maxHeap[child] = temp;
            index = child;
        }
        else return;
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (index <= 0) return;
    int parent;
    while (maxHeap[index] > maxHeap[parent = (index-1)/2]) {
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[parent];
        maxHeap[parent] = temp;
        index = parent;
    }
}

template <typename T>
void heapSort(T* start, T* end) {
    int size = end - start;
    int* maxHeap = new int[size];
    for (int i = 0; i < size; i++) {
        maxHeap[i] = start[i];
        reheapUp(maxHeap, i, i);
    }
    for (int i = 0; i < size; i++) {
        cout << maxHeap[i] << " ";
    }
    cout << endl;
    for (int i = size-1; i >= 0; i--) {
        cout << i << endl;
        start[i] = maxHeap[0];
        maxHeap[0] = maxHeap[i];
        reheapDown(maxHeap, i, 0);
        for (int j = 0; j < i; j++) {
            cout << maxHeap[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int arr[] = { -1, 0, 2, 3 };
    int n = sizeof arr / sizeof arr[0];
    heapSort(arr, arr + n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}