/*
 * totalpass of an element x in an array, means the number of elements in the array larger than x,
 * find the maximum totalpass in the array
 * */
#include <iostream>
#include <vector>
using namespace std;

int totalPass(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    int size = nums.size(), minVal = nums[0];
    for (int i = 1; i < size; i++) {
        minVal = min(minVal, nums[i]);
    }
    int count = 0;
    for (auto num : nums) {
        if (num > minVal) {
            count++;
        }
    }
    return count;
}

int main() {
    int nums[] = {1, 2, 1};
    vector<int> vnums(nums, nums + sizeof(nums) / sizeof(int));
    int count = totalPass(vnums);
    cout<<"count:"<<count<<endl;
    return 0;
}