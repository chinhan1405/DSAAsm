#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

public:
    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
        for (int i=segment_idx; i<(end-start)-cur_segment_total; i+=cur_segment_total) {
            int min_index = i;
            for (int j=i+cur_segment_total; j<end-start; j+=cur_segment_total) {
                if (start[j] < start[min_index]) {
                    min_index = j;
                }
            }
            if (min_index > i) {
                T temp = start[i];
                start[i] = start[min_index];
                start[min_index] = temp;
            }
        }
    }

    static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
        for (int i = 0; i < num_phases; i++) {
            int cur_segment_total = num_segment_list[num_phases-i-1];
            for (int j = 0; j < cur_segment_total; j++) {
                sortSegment(start, end, j, cur_segment_total);
            }
            cout << cur_segment_total << " segments: ";
            printArray(start, end);
        }
        
    }
};

int main() {
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
}