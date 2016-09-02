#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int filePathSum(string str);
    int imageDirPathSum(string str);
};

int Solution::imageDirPathSum(string str) {
    vector<string> paths;
    int oldPos = 0, pos;

    str.push_back('\n');
    pos = str.find_first_of('\n', oldPos);
    while (pos != string::npos) {
        string curPath = str.substr(oldPos, pos - oldPos);
        if (!curPath.empty()) {
            paths.push_back(curPath);
        }
        oldPos = pos + 1;
        pos = str.find_first_of('\n', oldPos);
    }
    int sumPath = 0, curPath = 0;
    stack<pair<int, bool> > s;
    for (auto path : paths) {
        int level = 0, len = path.length();
        while (level < len && path[level] == ' ') level++;
        path = path.substr(level);

        while (s.size() > level) {
            curPath -= (s.top()).first;
            s.pop();
        }
        if (path.find(".jpeg") != string::npos || path.find(".png") != string::npos || path.find(".gif") != string::npos) {
            pair<int, bool> p = s.top();
            if ((s.top()).second == false) {
                sumPath += curPath;
                (s.top()).second = true;
            }
        }
        int curLen = path.length() + 1;
        curPath += curLen;
        s.push(make_pair(curLen, false));
    }
    return sumPath;
}

int Solution::filePathSum(string str) {
    vector<string> paths;
    int oldPos = 0, pos;

    str.push_back('\n');
    pos = str.find_first_of('\n', oldPos);
    while (pos != string::npos) {
        string curPath = str.substr(oldPos, pos - oldPos);
        if (!curPath.empty()) {
            paths.push_back(curPath);
        }
        oldPos = pos + 1;
        pos = str.find_first_of('\n', oldPos);
    }

    int sumPath = 0, curPath = 0;
    stack<int> s;
    for (auto path : paths) {
        int level = 0, len = path.length();
        while (level < len && path[level] == ' ') level++;
        path = path.substr(level);

        while (s.size() > level) {
            curPath -= s.top();
            s.pop();
        }
        int curLen = path.length() + 1;
        curPath += curLen;
        if (path.find(".jpeg") != string::npos || path.find(".gif") != string::npos || path.find(".png") != string::npos) {
            sumPath = (sumPath + curPath) % 1000000007;
        }
        s.push(curLen);
    }
    return sumPath;
}

int main() {
    string path = "dir1\n dir11\n dir12\n  picture.jpeg\n  dir121\n  file1.txt\ndir2\n file2.gif";
    Solution s;
    int sumPath = s.filePathSum(path);
    cout<<"sumPath:"<<sumPath<<endl;
    string path2 = "dir1\n dir11\n dir12\n  picture.jpeg\n  dir121\n  file1.txt\n  test.png\ndir2\n file2.gif";
    int dirPath = s.imageDirPathSum(path2);
    cout<<"directory path:"<<dirPath<<endl;
}
