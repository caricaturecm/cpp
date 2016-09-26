#include <vector>
//#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>
using namespace std;

vector<string> wellFit(int n, vector<pair<int, int> >& lights, vector<pair<int, int> >& checkPoints) {
    int lightCount = lights.size();
    unordered_map<int, int> rowLights, colLights, diagLights, antiDiagLights;

    set<pair<int, int> > uniqueLights(lights.begin(), lights.end());//avoid duplicate lights???

    for (auto it = uniqueLights.begin(); it != uniqueLights.end(); it++) {
        rowLights[it->first]++;
        colLights[it->second]++;
        diagLights[it->first - it->second]++;
        antiDiagLights[it->first + it->second]++;
    }

    int curRow, curCol, curDiag, curAntiDiag, row, col;
    int checkCount = checkPoints.size();
    vector<string> ret;
    for (int i = 0; i < checkCount; i++) {
        curRow = 0;
        curCol = 0;
        curDiag = 0;
        curAntiDiag = 0;
        
        row = checkPoints[i].first;
        col = checkPoints[i].second;
        curRow = rowLights[row];
        curCol = colLights[col];
        curDiag = diagLights[row - col];
        curAntiDiag = antiDiagLights[row + col];
        if (uniqueLights.count(checkPoints[i])) {//current point
            curRow--;
            curCol--;
            curDiag--;
            curAntiDiag--;
        }
        if (col - 1 >= 1 && uniqueLights.count(make_pair(row, col - 1))) {
            curRow--;
        }
        if (row + 1 <= n && col - 1 >= 1 && uniqueLights.count(make_pair(row + 1, col - 1))) {
            curAntiDiag--;
        }
        if (row + 1 <= n && uniqueLights.count(make_pair(row + 1, col))) {
            curCol--;
        }
        if (row + 1 <= n && col + 1 <= n && uniqueLights.count(make_pair(row + 1, col + 1))) {
            curDiag--;
        }
        if (col + 1 <= n && uniqueLights.count(make_pair(row, col + 1))) {
            curRow--;
        }
        if (row - 1 >= 1 && col + 1 <= n && uniqueLights.count(make_pair(row - 1, col + 1))) {
            curAntiDiag--;
        }
        if (row - 1 >= 1 && uniqueLights.count(make_pair(row - 1, col))) {
            curCol--;
        }
        if (row - 1 >= 1 && col - 1 >= 1 && uniqueLights.count(make_pair(row - 1, col - 1))) {
            curDiag--;
        }

        if (curRow || curCol || curDiag || curAntiDiag) {
            ret.push_back("Light");
        } else {
            ret.push_back("Dark");
        }
    }
    return ret;
}

int main() {
    vector<pair<int, int> > lights;
    lights.push_back(make_pair(1, 6));
    lights.push_back(make_pair(5, 6));
    lights.push_back(make_pair(7, 3));
    lights.push_back(make_pair(3, 2));

    vector<pair<int, int>> queries;
    queries.push_back(make_pair(4, 4));
    queries.push_back(make_pair(6, 6));
    queries.push_back(make_pair(8, 1));
    queries.push_back(make_pair(3, 2));
    queries.push_back(make_pair(2, 3));

    vector<string> ret = wellFit(8, lights, queries);
    for (auto r : ret) {
        cout<<r<<endl;
    } 
    return 0;
}
