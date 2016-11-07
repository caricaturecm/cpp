//
// Created by ChenMin on 10/2/16.
//
/*
 * the perimeter of an island in the matrix
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Island {
public:
    int islandPerimeter(vector<vector<int>>& matrix, int i, int j) {
        if (matrix.empty() || matrix[0].empty() || matrix[i][j] == 0) {
            return 0;
        }
        int row = matrix.size(), col = matrix[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        int perimeter = 0;
        queue<pair<int, int>> curLevel;
        curLevel.push(make_pair(i, j));
        visited[i][j] = true;

        bfs(matrix, curLevel, perimeter, visited);
        return perimeter;
    }

private:
    void bfs(vector<vector<int>>& matrix, queue<pair<int, int>>& curLevel, int& perimeter, vector<vector<bool>>& visited) {
        queue<pair<int, int>> nextLevel;

        int i, j;
        while (!curLevel.empty()) {
            auto p = curLevel.front();
            curLevel.pop();
            i = p.first;
            j = p.second;
            int neighbors = 0;
            if (i > 0 && matrix[i - 1][j] == 1) {
                neighbors++;
                if (!visited[i - 1][j]) {
                    nextLevel.push(make_pair(i - 1, j));
                    visited[i - 1][j] = true;
                }
            }
            if (i + 1 < matrix.size() && matrix[i + 1][j] == 1) {
                neighbors++;
                if (!visited[i + 1][j]) {
                    nextLevel.push(make_pair(i + 1, j));
                    visited[i + 1][j] = true;
                }
            }
            if (j > 0 && matrix[i][j - 1] == 1) {
                neighbors++;
                if (!visited[i][j - 1]) {
                    nextLevel.push(make_pair(i, j - 1));
                    visited[i][j - 1] = true;
                }
            }
            if (j + 1 < matrix[0].size() && matrix[i][j + 1] == 1) {
                neighbors++;
                if (!visited[i][j + 1]) {
                    nextLevel.push(make_pair(i, j + 1));
                    visited[i][j + 1] = true;
                }
            }
            perimeter += (4 - neighbors);
        }
        if (!nextLevel.empty()) {
            bfs(matrix, nextLevel, perimeter, visited);
        }
    }
};

int main() {
    int row1[] = {0, 1, 1, 0, 0};
    int row2[] = {0, 0, 1, 0, 0};
    int row3[] = {0, 0, 1, 1, 1};
    int row4[] = {1, 1, 1, 0, 0};
    vector<vector<int>> matrix;
    matrix.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));
    matrix.push_back(vector<int>(row2, row2 + sizeof(row2) / sizeof(int)));
    matrix.push_back(vector<int>(row3, row3 + sizeof(row3) / sizeof(int)));
    matrix.push_back(vector<int>(row4, row4 + sizeof(row4) / sizeof(int)));

    Island island;
    int ret = island.islandPerimeter(matrix, 0, 1);
    cout<<"ret:"<<ret<<endl;
    return 0;
}