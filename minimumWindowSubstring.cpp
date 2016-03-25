//76. Minimum Window Substring
/*
 *The run time complexity of this alg is not very effective, should research more effective alg for this question 
 * */
class Solution {
    public:
        string minWindow(string s, string t) {
            string ret = "";
            if (s.empty() || t.empty() || s.length() < t.length()) {
                return ret;
            }

            int lens = s.length(), lent = t.length();
            unordered_map<char, int> smap, tmap;//unordered_map is easy to use in C++, ++ and -- both are based on 0

            for (auto ch : t) {
                tmap[ch]++;//regardless the existence of the key ch, ++ directly
            }

            int minLen = INT_MAX, matchCount = 0;
            for (int slow = 0, fast = 0; fast < lens; fast++) {
                char c = s[fast];
                if (tmap.find(c) != tmap.end()) {
                    smap[c]++;
                    if (smap[c] <= tmap[c]) {
                        matchCount++;
                    }
                }

                //when match all the characters in t, update the slow, and the candidate substr
                if (matchCount == lent) {
                    while (tmap.find(s[slow]) == tmap.end() || smap[s[slow]] > tmap[s[slow]]) {
                        smap[s[slow]]--;//should before the slow++
                        slow++;
                    }
                    if (fast - slow + 1 < minLen) {
                        minLen = fast - slow + 1;
                        ret = s.substr(slow, fast - slow + 1);
                    }
                }
            }

            return ret;
        }
};
