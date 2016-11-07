//
// Created by ChenMin on 10/11/16.
//
/*
 * 给一个matrix含有0: 障碍物 1：人类 2：僵尸。
 * 每一天僵尸可以把身边最近的人变成僵尸，但无法通过障碍。 求一共需要多少天把所有人变成僵尸。
 *
 * http://www.1point3acres.com/bbs/thread-193919-1-1.html
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int countDepth(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return -1;
        }
        int row = matrix.size(), col = matrix[0].size();
        queue<pair<int, int>> zombies;
        for (int i = 0; i < row; i++) {//store all the zombies at the beginning
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == 2) {
                    zombies.push(make_pair(i, j));
                }
            }
        }

        int days = bfs(matrix, zombies);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == 1) {
                    return -1;//some people can not reached by zombie
                }
            }
        }
        return days;
    }
private:
    int bfs(vector<vector<int>>& matrix, queue<pair<int, int>>& curLevel) {
        int days = 0;

        while (!curLevel.empty()) {
            days++;
            queue<pair<int, int>> nextLevel;

            while (!curLevel.empty()) {
                auto item = curLevel.front();
                int x = item.first, y = item.second;
                curLevel.pop();
                if (x > 0 && matrix[x - 1][y] == 1) {
                    matrix[x - 1][y] = 2;
                    nextLevel.push(make_pair(x - 1, y));
                }
                if (x + 1 < matrix.size() && matrix[x + 1][y] == 1) {
                    matrix[x + 1][y] = 2;
                    nextLevel.push(make_pair(x + 1, y));
                }
                if (y > 0 && matrix[x][y - 1] == 1) {
                    matrix[x][y - 1] = 2;
                    nextLevel.push(make_pair(x, y - 1));
                }
                if (y + 1 < matrix[0].size() && matrix[x][y + 1] == 1) {
                    matrix[x][y + 1] = 2;
                    nextLevel.push(make_pair(x, y + 1));
                }
            }
            curLevel = nextLevel;
        }
        return days - 1;//level, the count of edges
    }
};


int main() {
    int row1[] = {1, 0, 1, 0};
    int row2[] = {2, 1, 1, 1};
    int row3[] = {1, 1, 2, 1};
    int row4[] = {2, 1, 1, 1};
    vector<int> vrow1(row1, row1 + sizeof(row1) / sizeof(int));
    vector<int> vrow2(row2, row2 + sizeof(row2) / sizeof(int));
    vector<int> vrow3(row3, row3 + sizeof(row3) / sizeof(int));
    vector<int> vrow4(row4, row4 + sizeof(row4) / sizeof(int));
    vector<vector<int>> matrix;
    matrix.push_back(vrow1);
    matrix.push_back(vrow2);
    matrix.push_back(vrow3);
    matrix.push_back(vrow4);

    Solution sol;
    int days = sol.countDepth(matrix);
    cout<<"days:"<<days<<endl;
    return 0;
}