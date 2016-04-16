/*Input: a sequence of n positive intergers, an interger k
 * Output: the number of subarrsy in the array, that can be divisible by k
 * */
#include <iostream>
#include <vector>
using namespace std;

long long countDivK(vector<int>& nums, int k) {
    vector<int> countMod(k, 0);
    countMod[0] = 1;//the left most array, an empty array
    int preSum = 0;

    for (auto elem : nums) {
        preSum += elem;
        preSum %= k;
        countMod[preSum]++;
    }

    long long ret = 0;
    for (int mod = 0; mod < k; mod++) {
        //select two presum with the same remain number. left one and right one. 
        ret += (long long)(countMod[mod] * (countMod[mod] - 1)) / 2;
    }
}

int main() {
    
}
