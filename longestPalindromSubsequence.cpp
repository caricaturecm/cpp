#include <iostream>
#include <vector>
using namespace std;

//longest Palindrome Subsequences
int lps(string str) {
    int len = str.length();
    vector<vector<int> > dp(len, vector<int>(len, 0));//二维数组
    for (int i = 0; i < len; i++) {//every character is a palindrome itself
        dp[i][i] = 1;
    }

    //only the upper half the matrix
    //computer diagonal one by one, first the longest diagonal, then the minus one, then go on, until go to the rightest
    //number in the matrix
    //down up, diagonal number + 2, or the max num of the left or down number in the matrix
    for (int i = 1; i < len; i++) {//the number of diagonal, up
        for (int j = 0; j + i < len; j++) {
            int tmp;
            if (str[j] == str[j + i]) {
                tmp = dp[j + 1][j + i - 1] + 2;
            } else {
                tmp = max(dp[j + 1][j + i], dp[j][j + i - 1]);
            }
            dp[j][j + i] = tmp;
        }
    }
    return dp[0][len - 1];
}

int main() {
    int ret = lps("bcb");
    cout<<"ret:"<<ret<<endl;
    return 1;
}
