//123. Best Time to Buy and Sell Stock III
class Solution {
    public:
        int maxProfit(vector<int>& prices);
};

int Solution::maxProfit(vector<int>& prices) {
    int arr[] = {INT_MIN, 0, INT_MIN, 0};
    vector<int> initial(arr, arr + 4);
    vector<vector<int>> actions(2, initial);
    int current = 0, next = 1;

    for (auto price : prices) {
        actions[next][0] = max(actions[current][0], -price);//buy first
        actions[next][1] = max(actions[current][1], actions[current][0] + price);//sell first
        actions[next][2] = max(actions[current][2], actions[current][1] - price);//buy second
        actions[next][3] = max(actions[current][3], actions[current][2] + price);//sell second
        if (current == 0) {
            current = 1;
            next = 0;
        } else {
            current = 0;
            next = 1;
        }
    }

    return actions[current][3];
}

