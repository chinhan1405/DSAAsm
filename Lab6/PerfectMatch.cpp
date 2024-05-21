#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int pairMatching(vector<int>& nums, int target) {
    unordered_map<int, int> m;
    int count = 0;
    for (int num : nums) {
        if (m.find(target-num)!=m.end() && m[target-num]!=0) {
            count++;
            m[target-num]--;
        }
        else if (m.find(num) == m.end()) {
            m[num] = 1;
        }
        else {
            m[num]++;
        }
    }
    return count;
}

int main() {
    vector<int>items{1, 3, 5, 3, 7};
    int target = 6;
    cout << pairMatching(items, target);
}