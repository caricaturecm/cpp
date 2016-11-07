//
// Created by ChenMin on 10/1/16.
//
/**
 * given an equation of x and y, compute the relation between then
 *
 * Then, given x, return y
 *
 */
#include <iostream>
#include <stack>
#include <vector>
#include <limits>
using namespace std;


class GetY {
public:
    double getY(string& s, int x) {
        if (s.empty()) {
           // return -1;//not sure
            return numeric_limits<double>::min();
        }
        int countx = 0, county = 0, num = 0, curNum = 0, len = s.length();
        bool reverse = false;
        char op = '+';
        for (int i = 0; i < len; i++) {
            if (isdigit(s[i])) {
                curNum = curNum * 10 + (s[i] - '0');
            } else if (isspace(s[i])) {
                continue;
            } else {
                if (s[i] == '+' || s[i] == '-' || s[i] == '=') {
                    num += (op == '+') ? curNum : -curNum;
                    curNum = 0;
                    if (s[i] == '+' || s[i] == '-') {
                        if (reverse) {
                            op = s[i] == '+' ? '-' : '+';
                        } else {
                            op = s[i];
                        }
                    } else {
                        reverse = true;
                        op = '-';//one tricky
                    }
                } else if (s[i] == 'x') {
                    countx += op =='+' ? curNum : -curNum;
                    curNum = 0;
                } else {//y
                    county += op == '+' ? curNum : -curNum;
                    curNum = 0;
                }
            }
        }
        if (curNum) {//second tricky
            num += op == '+' ? curNum : -curNum;
        }
        if (county == 0) {
//            return -1;
            return numeric_limits<double>::min();
        }
        double y = (-countx * x - num) / county;
        return y;
    }

    double findYwithPar(string& s, int x) {
        if (s.empty()) {
//            return -1;
            return numeric_limits<double>::min();
        }
        auto pos = s.find('=');
        string left = s.substr(0, pos);
        string right = s.substr(pos + 1);

        vector<int> leftRet = getCounts(left);
        vector<int> rightRet = getCounts(right);
        cout<<"left:"<<left<<",right:"<<right<<endl;

        cout<<"left nums:"<<leftRet[0]<<","<<leftRet[1]<<","<<leftRet[2]<<endl;
        cout<<"right nums:"<<rightRet[0]<<","<<rightRet[1]<<","<<rightRet[2]<<endl;

        int countx = leftRet[0] - rightRet[0];
        int county = leftRet[1] - rightRet[1];
        int num = leftRet[2] - rightRet[2];
        if (county == 0) {
            //return DBL_MIN;
        }
        double y = (double)(-countx * x - num) / county;
        return y;
    }
private:
    vector<int> getCounts(string& s) {
        stack<int> countx;
        stack<int> county;
        stack<int> nums;
        stack<char> ops;
        int curCountx = 0, curCounty = 0, curNum = 0, digitNum = 0;
        char op = '+';
        int len = s.length();
        for (int i = 0; i < len; i++) {
            if (isdigit(s[i])) {
                digitNum = digitNum * 10 + (s[i] - '0');
            } else if (isspace(s[i])) {
                continue;
            } else {
                if (s[i] == 'x') {
                    curCountx += op == '+' ? digitNum : -digitNum;
                    digitNum = 0;
                    op = '+';
                } else if (s[i] == 'y') {
                    curCounty += op =='+' ? digitNum : -digitNum;
                    digitNum = 0;
                    op = '+';
                } else {
                    curNum += op == '+' ? digitNum : -digitNum;
                    digitNum = 0;
                    if (s[i] == '+' || s[i] == '-') {
                       op = s[i];
                    } else if (s[i] == '(') {
                        countx.push(curCountx);
                        curCountx = 0;
                        county.push(curCounty);
                        curCounty = 0;
                        nums.push(curNum);
                        curNum = 0;
                        ops.push(op);
                        op = '+';
                    } else if (s[i] == ')') {//')'
                        int preCountx = countx.top();
                        countx.pop();
                        int preCounty = county.top();
                        county.pop();
                        int preNum = nums.top();
                        nums.pop();
                        char preOp = ops.top();
                        ops.pop();

                        if (preOp == '+') {
                            curCountx += preCountx;
                            curCounty += preCounty;
                            curNum += preNum;
                        } else {
                            curCountx = preCountx - curCountx;
                            curCounty = preCounty - curCounty;
                            curNum = preNum - curNum;
                        }
                        op = '+';
                    }
                }
            }
        }
        if (digitNum) {
            curNum += op == '+' ? digitNum : -digitNum;
        }

        vector<int> ret;
        ret.push_back(curCountx);
        ret.push_back(curCounty);
        ret.push_back(curNum);
        return ret;
    }
};

int main() {
//    string str = "2x + 3y - 1 = 4x + 3y - 5";
    string str = "2    x     +    3     y      - 1      =     4x    - 2y + 4";
    GetY gy;
    double y = gy.getY(str, 5);
    cout<<"y:"<<y<<endl;

    string str1 = "2x + (3y + (- 1+ 2x)) = 4x - (2y + 4 - (2-3x))";
    y = gy.findYwithPar(str1, 5);
    cout<<"y:"<<y<<endl;
}