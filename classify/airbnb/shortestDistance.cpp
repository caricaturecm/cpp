 //
// Created by ChenMin on 10/14/16.
//

/*
 *
 *
 * EverString,
 * Given a number line from -infinity to +infinity. You start at 0 and can go either to the left or to the right.
 * The condition is that in i'th move, you take i steps.
 *
 * a) Find if you can reach a given number x
 * all the number x can be reached
 *
 * b) find the shortest number of steps to reach a number x
 * I think we can use bfs to get the shortest number of steps
 * */

/*
 * shortest distance,
 * http://www.1point3acres.com/bbs/thread-205518-1-1.html
 *
 * 一个二维vector named "people" :
{6,7}//people 0 knows people 6 7
{4}//people 1 knows people 4
...
一共10个数组。然后output出people 0到people 9的一个path，并且每一步的平方值加起来的cost 最小。
 比如0-1-2-3-4-5-6-7-8-9 比0-4-9的cost要少，(4-0)^2+(9-4)^2明显大
 * */
/*#include <iostream>
#include <vector>
using namespace std;

class Distance {
public:
//dijkstra, the shortest from source node to all the other nodes
    vector<int> dijkstra(vector<vector<int>>& graph, int s) {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<int> dist(n, INT_MAX);

        for (int i = 0; i < n; i++) {
            dist[i] = graph[s][i];
        }

        dist[s] = 0;
        visited[s] = true;

        for (int i = 1; i < n; i++) {//dist of other (n - 1) nodes
            int min = INT_MAX, next;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && dist[j] < min) {
                    min = dist[j];
                    next = j;
                }
            }
            visited[next] = true;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && (graph[next][j] != INT_MAX && dist[next] + graph[next][j] < dist[j])) {
                    dist[j] = dist[next] + graph[next][j];
                }
            }
        }
        return dist;
    }

    //for direction graph
    vector<vector<int>> floyd(vector<vector<int>>& graph, vector<vector<int>>& path) {
        int n = graph.size();
        vector<vector<int>> dist = graph;
        path.assign(n, vector<int>(n, -1));

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = k;
                    }
                }
            }
        }
        return dist;
    }

};

int main() {
    vector<vector<int>> graph(6, vector<int>(6, INT_MAX));
    graph[0][1] = 7;
    graph[0][2] = 14;
    graph[0][3] = 9;
    graph[1][0] = 7;
    graph[1][2] = 10;
    graph[1][5] = 15;
    graph[2][0] = 14;
    graph[2][3] = 2;
    graph[2][4] = 9;
    graph[3][0] = 9;
    graph[3][1] = 10;
    graph[3][2] = 2;
    graph[3][5] = 11;
    graph[4][2] = 9;
    graph[4][5] = 6;
    graph[5][1] = 15;
    graph[5][3] = 11;
    graph[5][4] = 6;

    Distance distance;
    vector<int> dis = distance.dijkstra(graph, 0);
    for (auto d : dis) {
        cout<<"dis:"<<d<<" ";
    }
    cout<<endl;

    vector<vector<int>> dirGraph(6, vector<int>(6, INT_MAX));
    dirGraph[0][1] = 7;
    dirGraph[0][2] = 14;
    dirGraph[0][3] = 9;
    dirGraph[1][2] = 10;
    dirGraph[1][5] = 15;
    dirGraph[3][2] = 2;
    dirGraph[2][4] = 9;
    dirGraph[3][5] = 11;
    dirGraph[4][5] = 6;

    cout<<"floyd path:"<<endl;
    vector<vector<int>> path;
    vector<vector<int>> mulDist = distance.floyd(dirGraph, path);
    for (auto dises : mulDist) {
        for (auto dis : dises) {
            if (dis == INT_MAX) {
                cout<<0<<" ";
            } else {
                cout << dis << " ";
            }
        }
        cout<<endl;
    }

    return 0;
}*/


/*vector<int> getMinPath(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> minDist(n, INT_MAX), preNode;
    visited[0] = true;//node 0 is the source node
    minDist[0] = 0;
    preNode.push_back(0);

    vector<int> dist;
    while (preNode.size() < n) {
        int pre = preNode.back();//pre node
        for (auto edge : graph[pre]) {
            minDist[edge] = min(minDist[edge], minDist[pre] + );
        }
    }

}*/


 /*
  * 一个二维vector named "people" :
{6,7}//people 0 knows people 6 7
{4}//people 1 knows people 4
一共10个数组。然后output出people 0到people 9的一个path，并且每一步的平方值加起来的cost 最小。
  比如0-1-2-3-4-5-6-7-8-9 比0-4-9的cost要少，(4-0)^2+(9-4)^2明显大。应该是使用Dijkstra最短路径，cost就是两点之间的平方和

  * */

#include <iostream>
#include <vector>
 using namespace std;

 class shortestPath {
 public:
     int minPath(vector<vector<int>>& graph) {
         vector<int> dist(10, INT_MAX);
         vector<bool> visited(10, false);
         int end = 9;

         dist[0] = 0;
         visited[0] = true;

         vector<int> path = graph[0];
         int minPath = INT_MAX, next = 0;
         for (auto p : path) {
             int curDis = p * p;
             if (!visited[p] && curDis < dist[p]) {
                 dist[p] = curDis;
                 if (curDis < minPath) {
                     minPath = curDis;
                     next = p;
                 }
             }
         }
         minPath = minPath == INT_MAX ? -1 : minPath;

         while (next != end && minPath != -1) {//end is people 9
             visited[next] = true;
             vector<int> path = graph[next];

             for (auto p : path) {
                 int curDis = abs(p - next) * abs(p - next);
                 if (!visited[p] && (dist[next] + curDis) < dist[p]) {
                     dist[p] = dist[next] + curDis;
                 }
             }

             minPath = INT_MAX;
             for (int i = 0; i < 10; i++) {
                 if (!visited[i] && dist[i] < minPath) {
                     minPath = dist[i];
                     next = i;
                 }
             }
             minPath = minPath == INT_MAX ? -1 : minPath;
         }
         return dist[9];
     }
 };

 int main() {
     vector<vector<int>> graph = {
             {1, 4},
             {},
            // {2},
             {3},
             {4},
             {5, 9},
             {6},
             {7},
             {8},
             {9}
     };

     shortestPath sol;
     int ret = sol.minPath(graph);
     cout<<"ret:"<<ret<<endl;

     return 0;
 }