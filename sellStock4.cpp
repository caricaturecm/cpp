//188. Best Time to Buy and Sell Stock IV
/*
 *Really don't understand sell stock problem very much, need to discuss when you have time
 * */
class Solution {
    public:
        int maxProfit(int k, vector<int>& prices) {
            int days = prices.size();
            if (k == 0 || days < 2) {
                return 0;
            }
            if (2*k >= days) {
                return greedyProfit(prices);
            }

            vector<int> status(2*k, 0);
            for (int i = 0; i < 2*k; i += 2) {
                status[i] = INT_MIN;
            }
            vector<vector<int>> dp(2, status);
            int current = 0, next = 1;

            for (auto price : prices) {
                dp[next][0] = max(dp[current][0], -price);
                dp[next][1] = max(dp[current][1], dp[current][0] + price);
                for (int i = 2; i < 2*k; i+=2) {
                    dp[next][i] = max(dp[current][i], dp[current][i - 1] - price);
                    dp[next][i+1] = max(dp[current][i+1], dp[current][i] + price);
                }
                if (current) {
                    current = 0;
                    next = 1;
                } else {
                    current = 1;
                    next = 0;
                }
            }
            return dp[current][2*k - 1];
        }

    private:
        int greedyProfit(vector<int>& prices) {
            int ret = 0;

            int prePrice = INT_MAX;
            for (auto price : prices) {
                if (price > prePrice) {
                    ret += (price - prePrice);
                }
                prePrice = price;
            }

            return ret;
        }
};
