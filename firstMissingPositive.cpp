/*
 * use the index of the array, only positive numbers, so index begin from 1, num = index + 1
 * swap the positive until it is at the positive it should be
 * the worst case is that all the numbers are not in the positive it should be, so n times swap
 * the amortized swap for each number is O(1),
 * so the total time complexity is O(n)
 * */
class Solution {
    public:
        int firstMissingPositive(vector<int>& nums) {
            int size = nums.size();
            for (int i = 0; i < size; i++) {
                while (nums[i] > 0 && nums[i] <= size && nums[nums[i] - 1] != nums[i]) {
                    swap(nums[i], nums[nums[i] - 1]);
                }
            }

            for (int i = 0; i < size; i++) {
                if (nums[i] != i + 1) {
                    return i + 1;
                }
            }

            return size + 1;
        }
};
