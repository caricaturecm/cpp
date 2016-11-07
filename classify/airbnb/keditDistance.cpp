/*#include <iostream>
#include <vector>
using namespace std;

int getDistance(string word, string target) {
    if (word.empty()) {
        return target.length();
    } else if (target.empty()) {
        return word.empty();
    }

    int row = word.length(), col = target.length();
    vector<int> preRow(col + 1, 0);
    for (int i = 0; i <= col; i++) {
        preRow[i] = i;
    }

    for (int i = 0; i < row; i++) {
        vector<int> curRow(col + 1, 0);
        curRow[0] = i + 1;
        for (int j = 1; j <= col; j++) {
            if (word[i] == target[j - 1]) {
                curRow[j] = preRow[j - 1];
            } else {
                curRow[j] = 1 + min(curRow[j - 1], min(preRow[j - 1], preRow[j]));
            }
        }
        preRow = curRow;
    }
    return preRow[col];
}

vector<string> getKEditDistance(vector<string>& words, string& target, int k) {
    int size = words.size();
    int dis;
    vector<string> ret;
    for (int i = 0; i < size; i++) {
        dis = getDistance(words[i], target);
        if (dis <= k) {
            ret.push_back(words[i]);
        }
    }
    return ret;
}

int main() {
    string wordslist[] = {"ab", "abcd", "abcde", "window", "win"};
    vector<string> words(wordslist, wordslist + 5);
    string target = "abc";
    int k = 2;

    vector<string> ret = getKEditDistance(words, target, k);
    for (int i = 0; i < ret.size(); i++) {
        cout<<ret[i]<<endl;
    }
}*/

/*
 * get the words that distance with the target word, smaller than k
 *
 * Use Trie tree to do improbement
 * */
/*#include <iostream>
#include <vector>
using namespace std;


class EditDistance {
public:

    vector<string> kEditDistance(vector<string>& dict, string& target, int k) {
        int n = target.length();
        root = new TrieNode(n + 1);

        for (int i = 0; i <= n; i++) {
            root->dp[i] = i;
        }

        vector<string> ret;
        for (auto word : dict) {
            int len = word.length();
            if (len < (n - k) || len > (n + k)) {
                cout<<"too long or too short:"<<word<<endl;
                continue;
            }
            int dis = insertWord(word, n + 1, target);
            if (dis <= k) {
                ret.push_back(word);
            }
        }
        return ret;
    }


private:
    struct TrieNode {
        TrieNode* next[26];
        vector<int> dp;

        TrieNode(int n) {
            memset(next, 0, sizeof(26));
            dp.assign(n, 0);
        }
    };

    int insertWord(string& word, int n, string& targetWord) {
        int len = word.length();
        TrieNode* p = root;

        for (int i = 0; i < len; i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode(n);
                TrieNode* pre = p;
                p = p->next[word[i] - 'a'];
                updateDistance(pre->dp, word[i], i, targetWord, p->dp);
            } else {
                p = p->next[word[i] - 'a'];
            }
        }

        return p->dp.back();
    }

    void updateDistance(vector<int>& preRow, char ch, int index, string& word, vector<int>& curRow) {
        curRow[0] = index + 1;
        for (int i = 0; i < word.length(); i++) {
            if (ch == word[i]) {
                curRow[i + 1] = preRow[i];
            } else {
                curRow[i + 1] = 1 + min(curRow[i], min(preRow[i], preRow[i + 1]));
            }
        }
    }

    TrieNode* root;
};



int main() {
    vector<string> dict = {
            "ab", "abcd", "abcde", "window", "win"
    };
    string target = "abc";
    int k = 2;

    EditDistance sol;
    vector<string> ret = sol.kEditDistance(dict, target, k);

    for (int i = 0; i < ret.size(); i++) {
        cout<<ret[i]<<endl;
    }

    return 0;
}*/


#include <iostream>
#include <vector>
using namespace std;

class EditDistance {
public:
    vector<string> kEditDistance(vector<string>& dict, string& targetWord, int k) {
        int n = targetWord.length();
        root = new TrieNode(n + 1);

        for (int i = 0; i <= n; i++) {
            root->distance[i] = i;
        }

        vector<string> ret;
        for (string word : dict) {
            int len = word.length();
            if (len < (n - k) || len > (n + k)) {
                cout<<"too short or too long."<<endl;
                continue;
            }

            int dis = insertWord(word, targetWord);
            if (dis <= k) {
                ret.push_back(word);
            }
        }
        return ret;

    }

private:
    struct TrieNode {
        TrieNode* next[26];
        vector<int> distance;

        TrieNode(int size) {
            memset(next, 0, sizeof(next));
            distance.assign(size, 0);
        }
    };

    int insertWord(string& word, string& targetWord) {
        int len = word.length();
        int n = targetWord.length();
        TrieNode* p = root;

        for (int i = 0; i < len; i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode(n + 1);
                TrieNode* pre = p;
                p = p->next[word[i] - 'a'];

                updateDistance(pre->distance, i, word[i], targetWord, p->distance);
            } else {
                p = p->next[word[i] - 'a'];
            }
        }
        return p->distance.back();
    }

    void updateDistance(vector<int>& preRow, int index, char ch, string& targetWord, vector<int>& curRow) {
        curRow[0] = index + 1;
        for (int i = 0; i < targetWord.length(); i++) {
            if (ch == targetWord[i]) {
                curRow[i + 1] = preRow[i];
            } else {
                curRow[i + 1] = 1 + min(curRow[i], min(preRow[i], preRow[i + 1]));
            }
        }
    }

    TrieNode* root;
};


int main() {
    vector<string> dict = {
            "ab", "abcd", "abcde", "window", "win"
    };
    string target = "abc";
    int k = 2;

    EditDistance sol;
    vector<string> ret = sol.kEditDistance(dict, target, k);

    for (int i = 0; i < ret.size(); i++) {
        cout<<ret[i]<<endl;
    }

    return 0;
}