//
// Created by ChenMin on 10/29/16.
//
/*
 * house robber，升级版，要返回最大值，和抢的房子的index
 * */
 #include <iostream>
 #include <vector>
using namespace std;

pair<int, string> robber(vector<int>& nums) {
    pair<int, string> ret;
    if (nums.empty()) {
        return ret;
    }
    int size = nums.size();

    int prePre, pre;
    string strPrePre, strPre;

    prePre= nums[0];
    strPrePre = "0";
    if (size == 1) {
        ret.first = prePre;
        ret.second = strPrePre;
        return ret;
    }

    if (nums[1] > nums[0]) {
        pre = nums[1];
        strPre = "1";
    } else {
        pre = nums[0];
        strPre = "0";
    }

    for (int i = 2; i < size; i++) {
        int cur;
        string curStr;
        if (nums[i] + prePre > pre) {
            cur = nums[i] + prePre;
            curStr = strPrePre + "," + to_string(i);
        } else {
            cur = pre;
            curStr = strPre;
        }
        prePre = pre;
        strPrePre = strPre;
        pre = cur;
        strPre = curStr;
    }
    ret.first = pre;
    ret.second = strPre;
    return ret;
};

int main() {
    int a[] = {100, 2, 6, 37, 23, 6};
    vector<int> nums(a, a + sizeof(a) / sizeof(int));
    pair<int, string> ret = robber(nums);

    cout<<"maxNum:"<<ret.first<<",index:"<<ret.second<<endl;
    return 0;
}
