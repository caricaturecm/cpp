//
// Created by ChenMin on 9/28/16.
//

/*
 * the number of islands with different shape
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Island {
public:
    int numberIslands(vector<vector<int> >& islands) {
        if (islands.empty() || islands[0].empty()) {
            return 0;
        }
        int row = islands.size(), col = islands[0].size();
        vector<vector<bool> > visited(row, vector<bool>(col, false));

        unordered_set<string> difIslands;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (!visited[i][j] && islands[i][j] == 1) {
                    vector<int> curIsland;
                    dfs(islands, i, j, visited, curIsland);
                    string strIsland = getStrIsland(curIsland);
                    difIslands.insert(strIsland);
                }
            }
        }
        return difIslands.size();
    }

private:
    string getStrIsland(vector<int> island) {
        string ret = "";
        int diff = island[0];
        for (auto is : island) {
            ret += to_string(is - diff);
        }
        return ret;
    }

    void dfs(vector<vector<int> >& islands, int i, int j, vector<vector<bool> >& visited, vector<int>& curIsland) {
        if (i < 0 || (i >= islands.size()) || j < 0 || j >= islands[0].size() || visited[i][j] || islands[i][j] != 1) {
            return;
        }
        visited[i][j] = true;
        int directions[][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
        int col = islands[0].size() + 1;//only the consecutive number maybe confused. break the consecutive, add 1
        curIsland.push_back(i * col + j);
        for (auto dir : directions) {
            int nx = i + dir[0];
            int ny = j + dir[1];
            dfs(islands, nx, ny, visited, curIsland);
        }
    }
};

int main() {
    vector<vector<int> > islands;
    /*int row0[] = {1, 0, 1, 0};
    int row1[] = {0, 1, 0, 0};
    int row2[] = {0, 0, 0, 0};
    int row3[] = {1, 0, 1, 0};
    int row4[] = {0, 1, 0, 0};
    islands.push_back(vector<int>(row0, row0 + 4));
    islands.push_back(vector<int>(row1, row1 + 4));
    islands.push_back(vector<int>(row2, row2 + 4));
    islands.push_back(vector<int>(row3, row3 + 4));
    islands.push_back(vector<int>(row4, row4 + 4));*/

    int row0[] = {0, 1, 1};
    int row1[] = {1, 0, 0};
    int row2[] = {0, 0, 0};
    int row3[] = {1, 1, 1};
    islands.push_back(vector<int>(row0, row0 + 3));
    islands.push_back(vector<int>(row1, row1 + 3));
    islands.push_back(vector<int>(row2, row2 + 3));
    islands.push_back(vector<int>(row3, row3 + 3));

    Island island;
    int count = island.numberIslands(islands);
    cout<<"count:"<<count<<endl;
    return 0;
}

