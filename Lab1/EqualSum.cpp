#include <iostream>
#include <vector>

using namespace std;

int sum(vector<int>& nums, int start, int stop) {
    if (stop < start) return 0;
    int sum = 0;
    for (int i=start; i<=stop; i++) {
        sum += nums[i];
    }
    return sum;
}

int equalSumIndex(vector<int>& nums) {
    if (nums.size() == 0) return -1;
    for (int i=0; i<nums.size(); i++) {
        if (sum(nums, 0, i-1)==sum(nums, i+1, nums.size()-1)) return i;
    }
    return -1;
}

int main() {
    vector<int> nums = {1, -1, 1, -1, 1};
    cout << equalSumIndex(nums);
    return 0;
}