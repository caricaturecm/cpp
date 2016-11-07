//
// Created by ChenMin on 10/14/16.
//
/*
 * Given 3 array of Strings.

Array one = {Red, Green, Blue}
Array two = {Large, Medium, Small}
Array three={giant, monster}

Print out combinations of all three array.

public void combination(String[][] arrays) {}

 LC, telephone numbers

 http://www.1point3acres.com/bbs/thread-140125-1-1.html
 * */
#include <iostream>
#include <vector>
using namespace std;

void backTrack(vector<vector<string>>& mapping, int index, vector<string>& cur, vector<vector<string>>& ret) {
    if (index == mapping.size()) {
        ret.push_back(cur);
        return;
    }
    vector<string> vals = mapping[index];
    int len = vals.size();
    for (int i = 0; i < len; i++) {
        cur.push_back(vals[i]);
        backTrack(mapping, index + 1, cur, ret);
        cur.pop_back();
    }
}

int main() {
    vector<vector<string>> mapping;
    vector<string> row1;
    row1.push_back("Red");
    row1.push_back("Green");
    row1.push_back("Blue");
    mapping.push_back(row1);

    vector<string> row2;
    row2.push_back("Large");
    row2.push_back("Medium");
    row2.push_back("Small");
    mapping.push_back(row2);

    vector<string> row3;
    row3.push_back("giant");
    row3.push_back("monster");
    mapping.push_back(row3);

    vector<vector<string>> ret;
    vector<string> cur;
    backTrack(mapping, 0, cur, ret);
    for (auto line : ret) {
        for (auto val : line) {
            cout<<val<<" ";
        }
        cout<<endl;
    }
    return 0;
}