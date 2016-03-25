//30. Substring with Concatenation of All Words
/*
 * This is a naive alg,
 * check every index, following with length num*len (the length of substring with all words)
 * using two map, first one is the appear times of each word in words
 * another is the substring word appear times, should be the same with the previous one
 * */
class Solution {
    public:
        vector<int> findSubstring(string s, vector<string>& words) {
            int n = s.length(), num = words.size(), len = words[0].length();

            unordered_map<string, int> wmap;
            for (auto word : words) {
                wmap[word]++;
            }

            vector<int> indices;
            for (int i = 0; i <= (n - num * len); i++) {
                unordered_map<string, int> smap;
                int j = 0;
                for (; j < num; j++) {
                    string curWord = s.substr(i + j * len, len);
                    if (wmap.find(curWord) != wmap.end()) {
                        smap[curWord]++;
                        if (smap[curWord] > wmap[curWord]) {
                            break;
                        }
                    } else {
                        break;
                    }
                }
                if (j == num) {
                    indices.push_back(i);
                }
            }

            return indices;
        }
};
