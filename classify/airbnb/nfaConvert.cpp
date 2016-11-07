//
// Created by ChenMin on 11/3/16.
//

/*
 * 给你一个字符对的转换matrix，表示这个字符对会转化成一个字符(但是有的字符对可能有多个能够转化成的字符，
 * 原文是nondeterministic)。以及若干个合法的终点(最顶上那一个点)状态，
 * 多次询问，每次一个字符串如果有一个方法能够走到合法状态就算是YES，否则NO
解法：记忆化搜索，记录所有中间状态。因为转化矩阵和合法终点都是固定的，某个字符串要不永远是YES，要不永远是NO。最好写个类因为他后来说的……

 可以想象成一个类，构造函数会把矩阵和accept传进去，然后每次的input是一个字符串。
 这个字符串经过若干次变换，每次变换长度减1，最后变成只有一个字符。Accept里面的任何一个字符都可以成为一个合法的最终状态
 * */

/*#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Transform {
public:
    Transform(vector<vector<string>>& matrix, string& converge) {
        dict = matrix;
        end = converge;
    }

    bool isConverge(string str) {
        if (m.count(str)) {
            return m[str];
        }

        bool ret = false;
        if (str.empty()) {
            ret = end.empty();
            m[str] = ret;
            return ret;
        }

        int len = str.length();
        if (len == 1) {
            int pos = end.find(str[0]);
            ret = pos == string::npos ? false : true;
            m[str] = ret;
            return ret;
        }

        for (int i = 0; i + 1 < len; i++) {
            int l = str[i] - 'A';
            int r = str[i + 1] - 'A';
            string to = dict[l][r];
            int lent = to.length();

            for (int j = 0; j < lent; j++) {
                string left = str.substr(0, i);
                string right = str.substr(i + 2);
                left.push_back(to[j]);
                left += right;
                if (isConverge(left)) {
                    m[str] = true;
                    return true;
                }
            }
        }
        m[str] = false;
        return false;
    }

private:
    vector<vector<string>> dict;
    string end;
    unordered_map<string, bool> m;
};

int main() {
    vector<vector<string>> dict = {
            {"B", "AC", "A"},
            {"C", "A", "C"},
            {"B", "C", "A"}
    };

    string end = "A";
    Transform sol(dict, end);
    string input = "BCAB";
    bool ret = sol.isConverge(input);

    cout<<"ret:"<<ret<<endl;

    return 0;
}*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Transform {
public:
    Transform(vector<vector<string>>& matrix, string& converge) {
        dict = matrix;
        end = converge;
    }

    bool isConverge(string str) {
        if (m.count(str)) {
            return m[str];
        }

        bool ret = false;
        if (str.empty()) {
            ret = end.empty();
            m[str] = ret;
            return ret;
        }

        int len = str.length();
        if (len == 1) {
            int pos = end.find(str[0]);
            ret = pos == string::npos ? false : true;
            m[str] = ret;
            return ret;
        }

        for (int i = 0; i + 1 < len; i++) {
            int l = str[i] - 'A';
            int r = str[i + 1] - 'A';
            string to = dict[l][r];

            int lent = to.length();
            for (int j = 0; j < lent; j++) {
                string left = str.substr(0, i) + to[j] + str.substr(i + 2);
                if (isConverge(left)) {
                    m[str] = true;
                    return true;
                }
            }
        }
        m[str] = false;
        return false;
    }

private:
    vector<vector<string>> dict;
    string end;
    unordered_map<string, bool> m;
};


int main() {
    vector<vector<string>> dict = {
            {"B", "AC", "A"},
            {"C", "A", "C"},
            {"B", "C", "A"}
    };

    string end = "BC";
    Transform sol(dict, end);
    string input = "ABC";
    bool ret = sol.isConverge(input);

    cout<<"ret:"<<ret<<endl;

    return 0;
}