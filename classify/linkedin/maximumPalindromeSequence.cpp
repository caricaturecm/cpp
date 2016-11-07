//
// Created by ChenMin on 10/24/16.
//

/*
 * maximum palindrome sequence
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int maximumPalindromeSequence(string& str) {
    int len = str.length();
    vector<vector<int>> dp(len, vector<int>(len, 0));

    for (int i = len - 1; i >= 0; i--) {
        for (int j = i; j < len; j++) {
            if (i == j) {
                dp[i][j] = 1;
            } else {
                if (str[i] == str[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
    }
    return dp[0][len - 1];
}

int main() {
    string str = "abbcdbbde";
    int ret = maximumPalindromeSequence(str);
    cout<<"ret:"<<ret<<endl;
}

