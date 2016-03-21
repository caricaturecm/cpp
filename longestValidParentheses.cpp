//32. Longest Valid Parentheses
/*
 * Really so clever, use dp, I think is easy to understand the alg based on stack
 * */
class Solution {
    public:
        int longestValidParentheses(string s) {
            int len = s.length(), maxLen = 0;
            vector<int> dp(len, 0);

            for (int i = 1; i < len; i++) {
                //only ')' can update the current length of valid parentheses
                if (s[i] == ')') {
                    if (s[i - 1] == '(') {//a new pair of (), for current position, based on dp[i - 2]
                        dp[i] = i > 2 ? dp[i - 2] + 2 : 2;
                        maxLen = max(maxLen, dp[i]);
                    } else {
                        int preMatchIndex = i - dp[i - 1] - 1;//between (preMatchIndex, i - 1] are valid parentheses
                        if (preMatchIndex >= 0 && s[preMatchIndex] == '(') {
                            dp[i] = dp[i - 1] + 2;//a new pair of (), update the value based on dp[i - 1]
                            if (preMatchIndex > 0) {//some other valid parentheses before preMatchIndex
                                dp[i] += dp[preMatchIndex - 1];
                            }
                        }
                        maxLen = max(maxLen, dp[i]);
                    }
                }
            }

            return maxLen;
        }
};
