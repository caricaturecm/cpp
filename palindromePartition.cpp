//131. Palindrome Partitioning
/*
 * How to analyze the time complexity of backtracking
 * 
 * For this problem,
 * For len = 3, has 1 * 3, 2 * 2, 3 * 1, times try, each try will scan the a string with length 1, 2, 3
 * */
class Solution {
    public:
        vector<vector<string>> partition(string s) {
            vector<vector<string>> ret;
            vector<string> cur;

            backTrack(s, 0, cur, ret);
            return ret;
        }

    private:
        void backTrack(string& s, int index, vector<string>& cur, vector<vector<string>>& ret) {
            if (index == s.length()) {
                ret.push_back(cur);
                return;
            }

            string curStr;
            for (int len = 1; index + len <= s.length(); len++) {
                curStr = s.substr(index, len);
                if (isPalindrome(curStr)) {
                    cur.push_back(curStr);
                    backTrack(s, index + len, cur, ret);
                    int count = len;
                    cur.pop_back();
                }
            }
        }

        bool isPalindrome(string& str) {
            int len = str.length();
            int low = 0, high = len - 1;
            while (low < high) {
                if (str[low] != str[high]) {
                    return false;
                }
                low++;
                high--;
            }
            return true;
        }
};
