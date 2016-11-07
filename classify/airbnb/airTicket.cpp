//
// Created by ChenMin on 11/2/16.
//

/*
 *
 * 1. mincost of flight from start to end if allowed at most k connections. 比如：
A->B, 100,
B->C, 100,
A->C, 500.
如果k是1的话，起点终点是A，C的话，那A->B->C最好, 我只想到BFS的解法。而且这题给的input给的是string和数字的混合形式，用C++parse好麻烦



 给一堆飞机票， 要求给出在从城市a到b，花钱最少，并且connection次数不超过k次的行程及价钱（connection可以理解为历经的城市）。
 理解题目跟讨论解法上花了很长时间，lz说了bfs的解法，小哥暗示了一下用dp，但lz是个渣渣，实在想不出来，最后写了个bfs的，显然不是面试小哥想要的。

比如要求 a 到 b， connection： 4

[a, d, 2], [a, b, 12], [d, b, 5]
结果应该是： a ->d, d->b, 7
 * */

/*
 * Dijstra, connections is the # of edges
 * */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


/*class Flight {
public:
    //pair<string, int>
    int minCostFlight(vector<string>& flights, int k, int start, int end) {
        vector<vector<pair<int, int>>> graphs(26, vector<pair<int, int>>{});
        buildGraph(flights, graphs);


        vector<unordered_map<int, pair<int, bool>>> dp(26, unordered_map<int, pair<int, bool>>{});//all the path to every city, with connection -> distance
        vector<pair<int, int>> path = graphs[start];
        dp[start][0] = make_pair(0, true);

        int minPath = INT_MAX, next = 0, preConNum = 1;
//        vector<bool> visited(26, false);
//        visited[start] = true;
        for (auto outpath : path) {
            if (outpath.second < minPath) {
                minPath = outpath.second;
                next = outpath.first;
            }
            dp[outpath.first][1] = make_pair(outpath.second, false);
        }

        while (next != end && minPath != -1) {//the shortest distance to end haven't computed
            cout<<"next:"<<next<<",end:"<<end<<", minPath:"<<minPath<<endl;
//            visited[next] = true;
            dp[next][preConNum].second = true;
            path = graphs[next];
            //minPath = INT_MAX;
            for (auto outpath : path) {
                int curConNum = preConNum + 1;
//                if (!visited[outpath.first]) {
//                if (dp[][]) {
                    if (dp[outpath.first].count(curConNum) == 0 ) {
                        dp[outpath.first][curConNum] = make_pair(minPath + outpath.second, false);
                    } else if (dp[outpath.first][curConNum].second == false && dp[outpath.first][curConNum].first > (minPath + outpath.second)) {
                        dp[outpath.first][curConNum].first = minPath + outpath.second;
                    }
//                }
            }

            minPath = INT_MAX;
            for (int i = 0; i < 26; i++) {
//                if (visited[i]) continue;
                unordered_map<int, pair<int, bool>> item = dp[i];
                for (auto p : item) {
                    if (p.second.second) continue;
                    if (p.second.first < minPath && ((i != end && p.first + 1 <= k) || (i == end && p.first <= k))) {
                        minPath = p.second.first;
                        preConNum = p.first;
                        next = i;
                    }
                }
            }
            minPath = minPath == INT_MAX ? -1 : minPath;
        }
        return minPath;
    }

private:
    void buildGraph(vector<string>& flights, vector<vector<pair<int, int>>>& graphs) {
        int pos, price, start, end;
        for (string flight : flights) {
            pos = flight.find_first_of(',');
            price = stoi(flight.substr(pos + 1));
            start = flight[0] - 'A';
            end = flight[pos - 1] - 'A';
            graphs[start].push_back(make_pair(end, price));
        }
    }
};

int main() {
    vector<string> flights;
    flights.push_back("A->B,100");
    flights.push_back("B->C,100");
    flights.push_back("A->C,500");
    flights.push_back("A->E,50");
    flights.push_back("E->B,30");
    flights.push_back("C->D,100");

    Flight flight;
    //k, start, end
    int ret = flight.minCostFlight(flights, 3, 0, 3);
    cout<<"ret:"<<ret<<endl;
    return 0;
}*/


class Flight {
public:
    pair<string, int> minCostFlight(vector<string>& flights, int start, int end, int k) {
        if (k < 1) {
            return make_pair("", -1);
        }
        vector<unordered_map<int, int>> graph(26, unordered_map<int, int>{});
        buildGraph(flights, graph);

        vector<unordered_map<int, Triple>> dp(26, unordered_map<int, Triple>{});
        unordered_map<int, int> path = graph[start];
        int minPath = INT_MAX, next, preConNum = 1;
        Triple triple1(0, true, "");
        dp[start][0] = triple1;

        for (auto outpath : path) {
            if (outpath.second < minPath) {
                minPath = outpath.second;
                next = outpath.first;
            }
            Triple triple2(outpath.second, false, string(1, 'A' + start));
            dp[outpath.first][1] = triple2;
        }

        while (next != end && minPath != -1) {
            cout<<"next:"<<next<<",end:"<<end<<", minPath:"<<minPath<<endl;
            path = graph[next];
            dp[next][preConNum].used = true;

            int curConNum = preConNum + 1;
            for (auto outpath : path) {
                if (dp[outpath.first].count(curConNum) == 0) {
                    Triple triple3(minPath + outpath.second, false, dp[next][preConNum].preSteps + string(1, 'A' + next));
                    dp[outpath.first][curConNum] = triple3;
                } else if (dp[outpath.first][curConNum].used == false && dp[outpath.first][curConNum].dis > (minPath + outpath.second)) {
                    dp[outpath.first][curConNum].dis = minPath + outpath.second;
                }
            }

            minPath = INT_MAX;
            for (int i = 0; i < 26; i++) {
                for (auto outpath : dp[i]) {
                    if (outpath.second.used) continue;
                    if (outpath.second.dis < minPath) {
                        if ((i != end && outpath.first + 1 <= k) || (i == end && outpath.first <= k)) {
                            minPath = outpath.second.dis;
                            preConNum = outpath.first;
                            next = i;
                        }
                    } else if (outpath.second.dis == minPath && outpath.first < preConNum) {
                        preConNum = outpath.first;
                        next = i;
                    }
                }
            }
            minPath = minPath == INT_MAX ? -1 : minPath;
        }

        if (minPath == -1) {
            return make_pair("", -1);
        } else {
            return make_pair(dp[end][preConNum].preSteps + string(1, 'A' + end), minPath);
        }
    }

private:
    struct Triple {
        int dis;
        bool used;
        string preSteps;

        Triple(int d = 0, bool u = false, string steps = "") : dis(d), used(u), preSteps(steps) {}
    };


    void buildGraph(vector<string>& flights, vector<unordered_map<int, int>>& graph) {
        int pos, price, start, end;
        for (auto flight : flights) {
            pos = flight.find_first_of(',');
            price = stoi(flight.substr(pos + 1));
            start = flight[0] - 'A';
            end = flight[pos - 1] - 'A';
            if (graph[start].count(end)) {//duplicate flight, with different prices
                graph[start][end] = min(graph[start][end], price);
            } else {
                graph[start][end] = price;
            }
        }
    }
};

int main() {
    vector<string> flights;
    flights.push_back("A->B,100");
    flights.push_back("B->C,100");
    flights.push_back("A->C,500");
    flights.push_back("A->E,50");
    flights.push_back("E->B,30");
    flights.push_back("C->D,100");

    Flight flight;
    //k, start, end
    pair<string, int> ret = flight.minCostFlight(flights, 0, 3, 3);
    cout<<"ret:"<<ret.first<<","<<ret.second<<endl;
    return 0;
}