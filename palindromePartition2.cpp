//132. Palindrome Partitioning II
/*
 * Scan from back to forth, every [i, j] substr will be validated 
 * During the scan, process the minimum cutNum in every position, the cutNums[i] means the cut number for substr [i, len - 1]
 *
 * Can also use this alg to do palindrome partition 1, scan from begin to end
 * */
class Solution {
    public:
        int minCut(string s) {
            int len = s.length();
            vector<vector<bool>> isPalindrome(len, vector<bool>(len, false));
            vector<int> cutNums(len, 0);

            for (int i = len - 1; i >= 0; i--) {
                cutNums[i] = len - i - 1;
                for (int j = i; j < len; j++) {
                    if (s[i] == s[j] && (j - i < 2 || isPalindrome[i + 1][j - 1])) {
                        isPalindrome[i][j] = true;
                        if (j == len - 1) {
                            cutNums[i] = 0;
                        } else {
                            cutNums[i] = min(cutNums[i], cutNums[j + 1] + 1);
                        }
                    }
                }
            }

            return cutNums[0];
        }
};
