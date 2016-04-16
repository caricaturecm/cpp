#include <iostream>
#include <vector>
using namespace std;

//an array, find out the maximum difference between any two elements such that larger element appears after the smaller
//number. If no such two numbers exist, return -1
int maxDiff(vector<int> nums) {
    int ret = -1, minElem = nums[0], size = nums.size();
    
    for (int i = 1; i < size; i++) {
        ret = max(ret, nums[i] - minElem);
        minElem = min(minElem, nums[i]);
    }

    return ret;
}

int main() {
    int a[] = {2, 3, 10, 6, 4, 8, 1};
    vector<int> nums(a, a + 7);
    cout<<maxDiff(nums)<<endl;
    return 0;
}
