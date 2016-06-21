/*
 *Always return the smallest number that larger than the target in the array
 * if the target is larger or equal to the largest number, return the first number
 * */
#include <iostream>
#include <vector>
using namespace std;

int bsLarger(vector<int> nums, int target) {
    int low = 0, high = nums.size() - 1, mid;
    int originalHigh = nums.size() - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (target == nums[mid]) {
            //if (mid == high) {
            if (mid == originalHigh) {
                return nums[0];
            } else {
                return nums[mid + 1];
            }
        } else if (target > nums[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return nums[low];
}

int main() {
    int a[] = {2, 4, 6, 8, 10};
    vector<int> nums(a, a + 5);
    int target = 4;
    int ret = bsLarger(nums, target);
    cout<<"ret:"<<ret<<endl;
}
