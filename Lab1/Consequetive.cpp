#include <iostream>
#include <vector>

using namespace std;

bool consecutiveOnes(vector<int>& nums) {
    // STUDENT ANSWER
    if (nums.size()==0) return true;
    if (nums.size()==1) return false;
    int i=0;
    bool flag = false;
    for (;i<nums.size()-1; i++) {
        if (nums[i]==1 && nums[i+1]==1) { flag = true;}
        else if (nums[i]==1 && nums[i+1]!=1) break;
    }
    for (i++;i<nums.size()-1;i++) {
        if (nums[i]==1) return false;
    }
    return flag;
}

int main() {
    vector<int> nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,1,1};
    cout << consecutiveOnes(nums);
    return 0;
}