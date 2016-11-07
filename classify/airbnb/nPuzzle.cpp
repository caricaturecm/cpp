//
// Created by ChenMin on 11/4/16.
//

/*
 * 实现一个sliding game，就是以前小时候玩的那种九宫格，九宫格，
 * 一共8个方块，从1-8，一个方块空出来，然后打乱之后通过SLIDE还原，
 * 这个题要推广到N宫格，先实现这个游戏，然后对于一个任意的BOARD，要你把他解出来，这道题之前在地里AIRBNB面经没看过，最后没写完。
 * */

/*#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;


struct Board {
    vector<vector<char>> board;
    string key, path;
    int manhatonDis, step;

    Board(string& str, int depth, string par) {
        path = par;
        step = depth;
        key = str;

        vector<char> line(3, ' ');
        board.assign(3, line);

        int x, y;
        for (int i = 0; i < 9; i++) {
            x = i / 3;
            y = i % 3;
            board[x][y] = str[i];
        }

        manhatonDis = depth;//depth + manhaton distance
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                manhatonDis += (abs(i - (board[i][j] - '1') / 3) + abs(j - (board[i][j] - '1') % 3));
            }
        }
    }

    bool moveLeft(string& nextBoard) {//move the empty grid to left
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (j > 0) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[i * 3 + j - 1]);
            return true;
        }
        return false;
    }

    bool moveRight(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (j < 2) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[i * 3 + j + 1]);
            return true;
        }
        return false;
    }

    bool moveDown(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }

        if (i < 2) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[(i + 1) * 3 + j]);
            return true;
        }
        return false;
    }

    bool moveUp(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (i > 0) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[(i - 1) * 3 + j]);
            return true;
        }
        return false;
    }
};



class NPuzzle {
public:
    NPuzzle() {
    }

    bool setInitialStatus(string& initial) {
        if (initial.length() != 9) {
            cout<<"input length is invalid."<<endl;
            return false;
        }
        initialStatus = initial;
        return true;
    }

    bool run() {
        unordered_set<string> visited;
        visited.insert(initialStatus);

        priority_queue<Board, vector<Board>, mycmp> boards;
        Board board(initialStatus, 0, "");
        boards.push(board);

        while (!boards.empty()) {
            Board curBoard = boards.top();
            cout<<"curBoard, key:"<<curBoard.key<<", dis:"<<curBoard.manhatonDis<<endl;
            boards.pop();

            if (isFinal(curBoard.key)) {
                printPath(curBoard);
                return true;
            }

            string nextBoard = "";
            if (curBoard.moveLeft(nextBoard)) {
                if (visited.count(nextBoard) == 0) {//unvisited
                    Board newBoard(nextBoard, curBoard.step + 1, curBoard.path + "1");
                    boards.push(newBoard);
                    visited.insert(nextBoard);
                }
            }

            if (curBoard.moveRight(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    Board newBoard(nextBoard, curBoard.step + 1, curBoard.path + "2");
                    boards.push(newBoard);
                    visited.insert(nextBoard);
                }
            }

            if (curBoard.moveDown(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    Board newBoard(nextBoard, curBoard.step + 1, curBoard.path + "3");
                    boards.push(newBoard);
                    visited.insert(nextBoard);
                }
            }

            if (curBoard.moveUp(nextBoard)){
                if (visited.count(nextBoard) == 0) {
                    Board newBoard(nextBoard, curBoard.step + 1, curBoard.path + "4");
                    boards.push(newBoard);
                    visited.insert(nextBoard);
                }
            }
        }
        return false;
    }

    void printPath(Board& board) {
        int len = board.path.length();
        for (int i = 0; i < len; i++) {
            switch(board.path[i]) {
                case '1':
                    cout<<"left->";
                    break;
                case '2':
                    cout<<"right->";
                    break;
                case '3':
                    cout<<"down->";
                    break;
                case '4':
                    cout<<"up->";
                    break;
            }
        }
        cout<<"success."<<endl;
    }

private:
    string initialStatus;

    bool isFinal(string& status) {
        if (status == "123456789") {
            return true;
        }
        return false;
    }

    struct mycmp {
        bool operator()(Board& a, Board& b) {
            return a.manhatonDis > b.manhatonDis;
        }
    };
};


int main() {
    NPuzzle sol;
    string initial = "123495786";
    sol.setInitialStatus(initial);

    bool ret = sol.run();

    cout<<"ret:"<<ret<<endl;
    return 0;
}*/


#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

struct Board {
    vector<vector<char>> board;
    int depth, manhatonDis;
    string path, key;

    Board(string& str, int step, string curPath) {
        vector<char> line(3, ' ');
        board.assign(3, line);

        key = str;

        for (int i = 0; i < 9; i++) {
            int x = i / 3;
            int y = i % 3;
            board[x][y] = str[i];
        }

        depth = step;
        path = curPath;
        manhatonDis = step;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                manhatonDis += (abs(i - (board[i][j] - '1') / 3) + abs(j - (board[i][j] - '1') % 3));
            }
        }
    }

    bool moveLeft(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (j > 0) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[i * 3 + (j - 1)]);
            return true;
        }
        return false;
    }

    bool moveRight(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (j < 2) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[i * 3 + j + 1]);
            return true;
        }
        return false;
    }

    bool moveDown(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (i < 2) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[(i + 1) * 3 + j]);
            return true;
        }
        return false;
    }

    bool moveUp(string& nextBoard) {
        int i, j;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (board[i][j] == '9') {
                    break;
                }
            }
            if (j != 3) {
                break;
            }
        }
        if (j > 0) {
            nextBoard = key;
            swap(nextBoard[i * 3 + j], nextBoard[(i - 1) * 3 + j]);
            return true;
        }
        return false;
    }
};

class NPuzzle {
public:
    void setInitialBoard(string& initial) {
        initialStr = initial;
    }

    bool run() {
        unordered_set<string> visited;
        visited.insert(initialStr);

        Board initialBoard(initialStr, 0, "");
        priority_queue<Board, vector<Board>, mycmp> boards;
        boards.push(initialBoard);

        while (!boards.empty()) {
            Board curBoard = boards.top();
            boards.pop();

            if (isFinal(curBoard.key)) {
                printPath(curBoard.path);
                return true;
            }

            string nextBoard = "";
            if (curBoard.moveLeft(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    visited.insert(nextBoard);

                    Board newBoard(nextBoard, curBoard.depth + 1, curBoard.path + "1");
                    boards.push(newBoard);
                }
            }

            if (curBoard.moveRight(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    visited.insert(nextBoard);

                    Board newBoard(nextBoard, curBoard.depth + 1, curBoard.path + "2");
                    boards.push(newBoard);
                }
            }

            if (curBoard.moveDown(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    visited.insert(nextBoard);

                    Board newBoard(nextBoard, curBoard.depth + 1, curBoard.path + "3");
                    boards.push(newBoard);
                }
            }

            if (curBoard.moveUp(nextBoard)) {
                if (visited.count(nextBoard) == 0) {
                    visited.insert(nextBoard);

                    Board newBoard(nextBoard, curBoard.depth + 1, curBoard.path + "4");
                    boards.push(newBoard);
                }
            }
        }
        return false;
    }

private:
    string initialStr;

    void printPath(string& path) {
        int len = path.length();
        for (int i = 0; i < len; i++) {
            switch(path[i]) {
                case '1':
                    cout<<"left->";
                    break;
                case '2':
                    cout<<"right->";
                    break;
                case '3':
                    cout<<"down->";
                    break;
                case '4':
                    cout<<"up->";
                    break;
                default:
                    break;
            }
        }
        cout<<"success."<<endl;
    }

    bool isFinal(string& str) {
        if (str == "123456789") {
            return true;
        }
        return false;
    }

    struct mycmp {
        bool operator()(Board& a, Board& b) {
            return a.manhatonDis > b.manhatonDis;
        }
    };
};


int main() {
    NPuzzle sol;
    string initial = "123495786";
    sol.setInitialBoard(initial);

    bool ret = sol.run();

    cout<<"ret:"<<ret<<endl;
    return 0;
}