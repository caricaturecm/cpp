//
// Created by ChenMin on 10/10/16.
//

/*
 *
有两个人A和B，给一个数组array，A和B轮流在这个array中取出数字，每次一个，并且只能取array第一个数字或者最后一个数字，
 取出数字后，array也随之更新，A先取，两人轮流，直到取完为止。A和B都相当相当相当的机智，
 他们都按照某个让自己最终能取出所有数字和最大的算法来取数字（这个算法是你要实现的），最后让你返回A最终得到的数字和。

当时电话面试，我也是理解了好久题目，给两个例子
例子1： array = {1，2，3}
            只能选头尾，A会先选3，B会选2，A接着选1，最后返回4。

例子2： array = {5, 9, 3, 1 }
            A先选：如果选5的话，虽然比尾部的1大，但是就把下一个较大的数字9让给了B，所以A先选1，
            B选：现在array变成了{5，9，3}，B会选5，.鐣欏璁哄潧-涓€浜�-涓夊垎鍦�
            A选：现在array变成了{9，3}，于是A开心的选了9，
            B选：现在array变成了{3}，于是B只能选3.
            所以返回和为 1+9=10。
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

//dp[i][j] means from i-->j, the maximum number A can get
class Solution {
public:
    int getMax(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int size = nums.size();
        dp.assign(size, vector<pair<int, int>>(size, pair<int, int>(0, 0)));

        int firNum, secNum;
        for (int i = size - 1; i >= 0; i--) {
            for (int j = i; j < size; j++) {
                if (i == j) {
                    firNum = nums[i];
                    secNum = 0;
                } else {
                    firNum = max(nums[i] + dp[i + 1][j].second, nums[j] + dp[i][j - 1].second);
                    secNum = dp[i][j - 1].first + dp[i][j - 1].second + nums[j] - firNum;
                }
                dp[i][j].first = firNum;
                dp[i][j].second = secNum;
            }
        }
        return dp[0][size - 1].first;
    }
private:
    vector<vector<pair<int, int>>> dp;
};


int main() {
//    int a[] = {3, 9, 1, 2};
//    int a[] = {5, 9, 3, 1};
    int a[] = {1, 2, 3};
    vector<int> nums(a, a + sizeof(a) / sizeof(int));

    Solution sol;
    int ret = sol.getMax(nums);
    cout<<"ret:"<<ret<<endl;
    return 0;
}