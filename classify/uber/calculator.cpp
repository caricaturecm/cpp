//
// Created by ChenMin on 10/11/16.
//

/*
 * 计算calculator，比如说计算：　１＋２*３/4, follow-up (1+2)*3 - 4*(5-8)这样的。需要写完，并且加些test　cases
 *
 * http://www.1point3acres.com/bbs/thread-189229-1-1.html
 * */
#include <iostream>
#include <stack>
using namespace std;

class Calculator {
public:
    long calculator(string str) {
        str.push_back('+');//for the last number
        stack<long> nums;
        stack<char> ops;

        int len = str.length();
        long curNum = 0;
        for (int i = 0; i < len; i++) {
            if (isdigit(str[i])) {
                curNum = curNum * 10 + (str[i] - '0');
            } else if (isspace(str[i])) {
                continue;
            } else {
                if (str[i] == '(') {
                    ops.push(str[i]);
                } else if (str[i] == ')') {
                    while (ops.top() != '(') {
                        long preNum = nums.top();
                        nums.pop();
                        char op = ops.top();
                        ops.pop();
                        switch (op) {
                            case '+' :
                                curNum += preNum;
                                break;
                            case '-':
                                curNum = preNum - curNum;
                                break;
//                            case '*':
//                                curNum *= preNum;
//                                break;
//                            case '/':
//                                curNum = preNum / curNum;
//                                break;
                            default:
                                break;
                        }
                    }
                    ops.pop();//pop the '('
                    //no need to push to nums, update the curNum
                  //  nums.push(curNum);
                    //curNum = 0;
                } else {
                    if (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
                        char preOp = ops.top();
                        ops.pop();
                        int preNum = nums.top();
                        nums.pop();
                        if (preOp == '*') {
                            curNum *= preNum;
                        } else {
                            curNum = preNum / curNum;
                        }
                    }
                    nums.push(curNum);
                    ops.push(str[i]);
                    curNum = 0;
                }

                /*else if (str[i] == '+' || str[i] == '-') {
                    if (!ops.empty() && ops.top() != '(') {
                        long preNum = nums.top();
                        nums.pop();
                        char op = ops.top();
                        ops.pop();
                        if (op == '+') {
                            curNum += preNum;
                        } else if (op == '-') {
                            curNum = preNum - curNum;
                        } else if (op == '*') {
                            curNum *= preNum;
                        } else if (op == '/') {
                            curNum = preNum / curNum;
                        }
                    }
                    ops.push(str[i]);
                    nums.push(curNum);
                    curNum = 0;
                } else if (str[i] == '*' || str[i] == '/') {
                    if (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
                        long preNum = nums.top();
                        nums.pop();
                        char op = ops.top();
                        ops.pop();
                        if (op == '*') {
                            curNum *= preNum;
                        } else {
                            curNum = preNum / curNum;
                        }
                    }
                    nums.push(curNum);
                    ops.push(str[i]);
                    curNum = 0;
                }*/
            }
        }
        ops.pop();//the last +
        while (!ops.empty()) {
            char op = ops.top();
            ops.pop();
            long num2 = nums.top();
            nums.pop();
            long num1 = nums.top();
            nums.pop();
            switch(op) {
                case '+':
                    curNum = num1 + num2;
                    break;
                case '-':
                    curNum = num1 - num2;
                    break;
//                case '*':
//                    curNum = num1 * num2;
//                    break;
//                case '/':
//                    curNum = num1 / num2;
//                    break;
                default:
                    break;
            }
            nums.push(curNum);
        }
        return nums.empty() ? 0 : nums.top();
    }
};

int main() {
    Calculator cal;
//    string str = "1 + 2 * 3 / 4 - 5 + 8 / 2 * 4 / 3 - 1 ";
//    string str = "(1 + 2) * 3 - 4 * (5 - 8)";
    string str = "(1 + 3) * 100 - 200 / (4 + 1 * 6 / 4 * 5 / 8 - 9)";
    long ret = cal.calculator(str);
    cout<<"ret:"<<ret<<endl;
    return 0;
}
