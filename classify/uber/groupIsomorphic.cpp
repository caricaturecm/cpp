//
// Created by ChenMin on 10/12/16.
//

/*
 * Group isomorphic(title,paper    egg,add    hello,billy)
 *
 * Similar: LC205, 290
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupIsomorphic(vector<string>& words) {
        unordered_map<string, vector<string>> groups;
        for (auto word : words) {
            string key = getKey(word);
//            cout<<"key:"<<key<<",word:"<<word<<endl;
            groups[key].push_back(word);
        }

        vector<vector<string>> ret;
        for (auto it = groups.begin(); it != groups.end(); it++) {
            ret.push_back(it->second);
        }
        return ret;
    }

private:
    string getKey(string& word) {
        unordered_map<char, int> m;
        int len = word.length();
        string key = "";

        for (int i = 0; i < len; i++) {
            if (m.count(word[i])) {
                key += (to_string(m[word[i]]) + "#");
            } else {
                m[word[i]] = i;
                key += (to_string(i) + "#");
            }
        }
        return key;
    }
};

int main() {
    vector<string> words;
    words.push_back("add");
    words.push_back("eggk");
    words.push_back("title");
    words.push_back("paper");
    words.push_back("min");

    Solution sol;
    vector<vector<string>> ret = sol.groupIsomorphic(words);
    for (auto vec : ret) {
        for (auto word : vec) {
            cout<<word<<" ";
        }
        cout<<endl;
    }
    return 0;
}