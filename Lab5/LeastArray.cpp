#include <iostream>
#include <vector>

using namespace std;

void reheapUp(int minHeap[], int numberOfElements, int index)
{
    if (index <= 0) return;
    int parent;
    while (minHeap[index] < minHeap[parent = (index-1)/2]) {
        int temp = minHeap[index];
        minHeap[index] = minHeap[parent];
        minHeap[parent] = temp;
        index = parent;
    }
}

void reheapDown(int minHeap[], int numberOfElements, int index)
{
    int child;
    while (true) {
        if (index*2 >= numberOfElements-1) return;
        int leftChild = index*2 + 1;
        int rightChild = index*2 + 2;
        if (minHeap[leftChild] > minHeap[rightChild]) {
            child = rightChild;
        }
        else {
            child = leftChild;
        }
        if (minHeap[index] > minHeap[child]) {
            int temp = minHeap[index];
            minHeap[index] = minHeap[child];
            minHeap[child] = temp;
            index = child;
        }
        else return;
    }
}

int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    int n = nums.size();
    int* minHeap = new int[n];
    for (int i = 0; i < n; i++) {
        minHeap[i] = nums[i];
        reheapUp(minHeap, i, i);
    }
    for (int i=0; i<k; i++) {
        int min = minHeap[0];
        minHeap[0] = minHeap[n-1];
        reheapDown(minHeap, n-1, 0);
        minHeap[n-1] = min * 2;
        reheapUp(minHeap, n, n-1);
    }
    return minHeap[0];
}

int main() {
vector<int> nums {2, 3, 5, 7};
int k = 3;
cout << leastAfter(nums, k);

}