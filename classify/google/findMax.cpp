//
// Created by ChenMin on 9/30/16.
//
/*
 * find the maximum number in an array, increasing first, then decreasing, both can be equal
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

class Peak {
public:
    int findMax(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }
private:
    int helper(vector<int>& nums, int low, int high) {
        cout<<"enter helper"<<endl;
        int mid, ret;
        while (low <= high) {
            mid = low + (high - low) / 2;
            cout<<"low:"<<low<<",high:"<<high<<",mid:"<<mid<<",nums[mid]:"<<nums[mid]<<endl;
            if (low == mid) {
                ret = max(nums[low], nums[high]);
                break;
            }
            if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
                ret = nums[mid];
                break;
            } else if (nums[mid] > nums[mid - 1]) {
                low = mid + 1;
            } else if (nums[mid] < nums[mid- 1]) {
                high = mid - 1;
            } else {
                int leftPeak = helper(nums, low, mid);
                int rightPeak = helper(nums, mid + 1, high);
                ret = max(leftPeak, rightPeak);
                break;
            }
        }
        return ret;
    }
};

int main() {
    int nums[] = {1, 2, 3, 3, 3, 5, 6, 8, 6, 3, 3, 3, 2, 2, 1};
    vector<int> vnums(nums, nums + sizeof(nums) / sizeof(int));
    Peak peak;
    int ret = peak.findMax(vnums);
    cout<<"ret:"<<ret<<endl;
    return 0;
}
