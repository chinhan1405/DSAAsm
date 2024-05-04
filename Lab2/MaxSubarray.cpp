#include<iostream>
#include<queue>
#include<vector>
#include<deque>
using namespace std;

int sumOfMaxSubarray(vector<int>& nums, int k) {
    deque<int> dq;
    int sum = 0;
    for (int i=0; i<k; i++) {
        while (!dq.empty() && nums[i] > nums[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    for (int i=k; i<nums.size(); i++) {
        sum += nums[dq.front()];
        while (!dq.empty() && dq.front() <= i-k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[i] > nums[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    sum += nums[dq.front()];
    return sum;
}

int main() {
    vector<int> nums {1, 2, 4, 3, 6};
    int k = 3;
    cout << sumOfMaxSubarray(nums, k);
}