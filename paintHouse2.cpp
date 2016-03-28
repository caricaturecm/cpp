//265. Paint House II
/*
 * This is so clever (I always say this after I find the soulution in the discuss panel)
 *
 * Actually can only use one vector, to combine the i = 0 into the for loop,
 * but, I think to use two vectors to represent preHouse and curHouse is easier to understand
 *
 * */
class Solution {
    public:
        int minCostII(vector<vector<int>>& costs) {
            int minC = 0;
            if (costs.empty() || costs[0].empty()) {
                return minC;
            }

            int n = costs.size(), k = costs[0].size();
            int preFirstMin = INT_MAX, preSecMin = INT_MAX;
            vector<int> preHouse = costs[0];
            /*
             * To find the second minimum number in an array, the same to find the second maximum
             * */
            for (auto cost : preHouse) {
                int curMin = min(preFirstMin, cost);
                int curMax = max(preFirstMin, cost);

                preFirstMin = min(curMin, preFirstMin);
                preSecMin = min(curMax, preSecMin);
            }

            for (int i = 1; i < n; i++) {
                int curFirstMin = INT_MAX, curSecMin = INT_MAX;
                vector<int> curHouse(k);

                for (int j = 0; j < k; j++) {
                    if (preHouse[j] == preFirstMin) {
                        curHouse[j] = preSecMin + costs[i][j];
                    } else {
                        curHouse[j] = preFirstMin + costs[i][j];
                    }

                    if (curHouse[j] <= curFirstMin) {
                        curSecMin = curFirstMin;
                        curFirstMin = curHouse[j];
                    } else if (curHouse[j] < curSecMin) {
                        curSecMin = curHouse[j];
                    }
                }

                preHouse = curHouse;
                preFirstMin = curFirstMin;
                preSecMin = curSecMin;
            }

            return preFirstMin;
        }
};
