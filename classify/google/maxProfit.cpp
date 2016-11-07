//
// Created by ChenMin on 10/26/16.
//
/*
 * http://www.1point3acres.com/bbs/thread-143308-1-1.html
 *
 * 题目：Given an array of Ad (profit, start_time, end_time) and a timespan [0, T],
 * find the max profit of Ads that fit the timespan.
小哥进来就说了句中文：怎么样啊？顿觉好温暖，中文寒暄了几句就用英文开始了。先说了穷举法O(2^n),
 然后说了贪心法（不是最优解），最后用DP解决。小哥态度灰常好，给了很有用的提示, 就像自家人啊。
 * */
#include <iostream>
#include <vector>
using namespace std;

struct Triple {
    int beginTime, endTime, profit;

    Triple(int btime, int etime, int pro) : beginTime(btime), endTime(etime), profit(pro) {}
};

class MaxProfit {
public:
    int maxProfit(vector<Triple>& ads) {
        if (ads.empty()) {
            return 0;
        }
        int size = ads.size();
        sort(ads.begin(), ads.end(), mycmp);
        vector<int> dp(size + 1, 0);
        dp[1] = ads[0].profit;

        for (int i = 2; i <= size; i++) {
            int index = lowerBound(ads, 0, i - 2, ads[i - 1].beginTime);
            dp[i] = max(dp[i - 1], dp[index + 1] + ads[i - 1].profit);
        }
        return dp[size];
    }

    //find the lastone that endtime is smaller or equal to the given endtime
    //no overlap between ads
    int lowerBound(vector<Triple>& ads, int begin, int end, int time) {
        if (ads[begin].endTime > time) {
            return -1;
        }
        if (ads[end].endTime <= time) {
            return end;
        }

        int low = begin, high = end, mid, ret;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (ads[mid].endTime <= time) {
                ret = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ret;
    }
private:
    bool static mycmp(Triple& a, Triple& b) {
        return a.endTime < b.endTime;
    }
};

int main() {
    vector<Triple> intervals;
    intervals.push_back(Triple(0, 4, 5));
    intervals.push_back(Triple(1, 3, 1));
    intervals.push_back(Triple(0, 1, 1));

    MaxProfit sol;
    int ret = sol.maxProfit(intervals);
    cout<<"ret:"<<ret<<endl;

    return 0;
}
