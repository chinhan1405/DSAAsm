#include <iostream>
#include <algorithm>
using namespace std;

void sortByFrequency(int arr[], int n){
    int* freq = new int[n];
    int* pos = new int[n];
    fill(freq, freq+n, 0);
    fill(pos, pos+n, 0);
    for (int i=0; i<n; i++) {
        freq[i] = count(arr, arr+n, arr[i]);
    }
    for (int i=0; i<n; i++) {
        pos[i] = find(arr, arr+n, arr[i]) - arr;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (freq[j] < freq[j+1] || (freq[j] == freq[j+1] && pos[j] > pos[j+1])) {
                swap(pos[j], pos[j+1]);
                swap(freq[j], freq[j+1]);
                swap(arr[j], arr[j+1]);
            }
        }
    
    }


}

int main() {
    int arr[] = {-4,1,2,2,-4,9,1,-1};
	int n = sizeof(arr) / sizeof(arr[0]);

	sortByFrequency(arr, n);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}