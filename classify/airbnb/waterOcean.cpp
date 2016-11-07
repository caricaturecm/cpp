//
// Created by ChenMin on 11/5/16.
//
/*
 * http://www.1point3acres.com/bbs/thread-141746-1-1.html
 *
 * Given: An array of strings where L indicates land and W indicates water,
*   and a coordinate marking a starting point in the middle of the ocean.
*
* Challenge: Find and mark the ocean in the map by changing appropriate Ws to Os.
*   An ocean coordinate is defined to be the initial coordinate if a W, and
*   any coordinate directly adjacent to any other ocean coordinate.
 *
 * */


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Water2Ocean {
public:
    Water2Ocean(vector<string>& grid) {
        this->grid = grid;
    }

    void toOcean(int x, int y) {
        int row = grid.size(), col = grid[0].size();
        if (x < 0 || x >= row || y < 0 || y >= col || grid[x][y] != 'W') {
            return;
        }

        grid[x][y] = 'O';
        queue<pair<int, int>> curLevel;
        curLevel.push(make_pair(x, y));
        bfs(grid, curLevel);
    }

    void printGrid() {
        for (auto str : grid) {
            cout<<str<<endl;
        }
    }

private:
    void bfs(vector<string>& grid, queue<pair<int, int>>& curLevel) {
        int row = grid.size(), col = grid[0].size();

        while (!curLevel.empty()) {
            auto item = curLevel.front();
            curLevel.pop();
            int x = item.first;
            int y = item.second;

            if (x > 0 && grid[x - 1][y] == 'W') {
                curLevel.push(make_pair(x - 1, y));
                grid[x - 1][y] = 'O';
            }
            if (x + 1 < row && grid[x + 1][y] == 'W') {
                curLevel.push(make_pair(x + 1, y));
                grid[x + 1][y] = 'O';
            }
            if (y > 0 && grid[x][y - 1] == 'W') {
                curLevel.push(make_pair(x, y - 1));
                grid[x][y - 1] = 'O';
            }
            if (y + 1 < col && grid[x][y + 1] == 'W') {
                curLevel.push(make_pair(x, y + 1));
                grid[x][y + 1] = 'O';
            }
        }
    }

    vector<string> grid;
};

int main() {

    vector<string> grid =  {
            "WWWLLW",
            "WWLLWW",
            "WWWLLW",
            "WWLLLL"
    };

    Water2Ocean sol(grid);
    sol.toOcean(2, 3);
    sol.printGrid();

    return 0;
}