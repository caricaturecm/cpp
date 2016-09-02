#include <iostream>
using namespace std;

class Solution {
public:
    int solution1(int x);
    int solution2(int x);
};

//Brute Force
int Solution::solution1(int x) {
    string strNum = to_string(x);
    int len = strNum.length();
    int smallestNum = INT_MAX, curNum;
    string curStr;
    for (int i = 0; i < len - 1; i++) {
        if (strNum[i] >= strNum[i + 1]) {
            curStr = strNum.substr(0, i + 1) + strNum.substr(i + 2);
        } else {
            curStr = strNum.substr(0, i) + strNum.substr(i + 1);
        }
        curNum = stoi(curStr);
        smallestNum = min(smallestNum, curNum);
    }
    return smallestNum;
}

//remove the middle one of first descenting three consecutive numbers
int Solution::solution2(int x) {
    string strNum = to_string(x);
    int len = strNum.length();
    if (len == 2) {
        if (strNum[0] >= strNum[1]) {
            return x / 10;
        } else {
            return x % 10;
        }
    }
    
    for (int i = 0; i < len - 2; i++) {
        if (strNum[i] >= strNum[i + 1] && strNum[i + 1] > strNum[i + 2]) {
            string curStr = strNum.substr(0, i + 1) + strNum.substr(i + 2);
            return stoi(curStr);
        }
    }

    string curStr = strNum.substr(0, len - 2);
    if (strNum[len - 2] >= strNum[len - 1]) {
        curStr += strNum.substr(len - 2);
    } else {
        curStr += strNum.substr(len - 1, 1);
    }
    return stoi(curStr);
}

int main() {
    int num = 36;
    Solution s;
    int ret1 = s.solution1(num);
    int ret2 = s.solution2(num);
    cout<<"num:"<<num<<", ret1:"<<ret1<<",ret2:"<<ret2<<endl;
    return 0;
}
