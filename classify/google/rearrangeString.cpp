//
// Created by ChenMin on 9/29/16.
//
/*
 *give a string, rearrange it, make sure the adjacent characters are different
 *
 * return all the possible string
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Rearrange {
public:
    vector<string> rearrangeStr(string& str) {
        unordered_map<char, int> counts;
        for (auto ch : str) {
            counts[ch]++;
        }

        vector<string> ret;
        string cur = "";
        backTrack(str, counts, cur, ret);
        return ret;
    }
private:
    void backTrack(string& str, unordered_map<char, int>& counts, string& cur, vector<string>& ret) {
        if (cur.length() == str.length()) {
            ret.push_back(cur);
            return;
        }
        for (auto count : counts) {
            if (count.second == 0 || (!cur.empty() && count.first == cur.back())) continue;
            cur.push_back(count.first);
            count.second--;
            backTrack(str, counts, cur, ret);
            count.second++;
            cur.pop_back();
        }
    }
};

int main() {
    string str = "adb";
    Rearrange re;
    vector<string> strs = re.rearrangeStr(str);
    for (auto ret : strs) {
        cout<<ret<<endl;
    }
    cout<<"string:"<<str<<endl;
}

