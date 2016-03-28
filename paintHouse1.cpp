//256. Paint House
/*
 * Should maintain the accumulate cost of every position (color), cannot simplily choose the current minimum color cost
 * for current house
 * */
class Solution {
    public:
        int minCost(vector<vector<int>>& costs) {
            int minC = 0;
            if (costs.empty() || costs[0].empty()) {
                return minC;
            }

            int houses = costs.size();
            vector<int> preHouse = costs[0];

            for (int i = 1; i < houses; i++) {
                vector<int> curHouse(3);
                curHouse[0] = min(preHouse[1], preHouse[2]) + costs[i][0];
                curHouse[1] = min(preHouse[0], preHouse[2]) + costs[i][1];
                curHouse[2] = min(preHouse[0], preHouse[1]) + costs[i][2];

                preHouse = curHouse;
            }
            return min(preHouse[0], min(preHouse[1], preHouse[2]));
        }
};
