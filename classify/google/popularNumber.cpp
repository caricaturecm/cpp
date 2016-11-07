//
// Created by ChenMin on 9/29/16.
//
/*
 * the minumum number that appears more than 1/4 * size in an sorted array, require O(lgN)
 *
 * the candidate number can only in positions 1/4, 2/4, 3/4, use binary search to find the range of the number in these positions
 * */

#include <iostream>
#include <vector>
using namespace std;
/*
 * Solution 1 : scan the positions 1/4, 2/4, 3/4
 *
 * smallest size of popular number is m = size / 4, then candidate positions are
 * (m - 1), (2m - 1), (3m - 1), (4m - 1), (5m - 1) --- (5m - 1) < n is possible
 * */

class Popular {
public:
    int popularNumber(vector<int>& nums) {
        int n = nums.size(), quad = n / 4;

        for (int i = 1; (i * quad - 1) < n; i++) {
            int index = i * quad - 1;
            int leftIndex = lowerBound(nums, nums[index]);
            int rightIndex = upperBound(nums, nums[index]);
            if (rightIndex - leftIndex >= quad) {
                return nums[index];
            }
        }
        return -1;//no such number

    }

    /*
    * Solution 2 : always verify the first candidate position, update the start position
    * */

    int popularNumber2(vector<int>& nums) {
        int size = nums.size(), quad = size / 4;
        int low = 0, pos = low + (quad - 1);
        while (pos < size) {
            if (nums[pos] == nums[low]) {
                return nums[pos];
            }
            low = upperBound(nums, nums[low]);
            pos = low + (quad - 1);
        }
        return -1;//no such number
    }

private:
    int lowerBound(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid, ret;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] >= target) {
                ret = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ret;
    }

    int upperBound(vector<int>& nums, int target) {
        if (target >= nums.back()) return nums.size();
        int low = 0, high = nums.size() - 1, mid, ret;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] > target) {
                ret = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ret;
    }
};




int main() {
    Popular pop;
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 12};
    vector<int> vnums(nums, nums + sizeof(nums) / sizeof(int));
    int ret = pop.popularNumber(vnums);
    cout<<"popular num:"<<ret<<endl;

    int ret2 = pop.popularNumber2(vnums);
    cout<<"pop number2:"<<ret2<<endl;
    return 0;
}