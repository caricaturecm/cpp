//
// Created by ChenMin on 11/3/16.
//
/*
 * http://www.1point3acres.com/bbs/thread-158462-1-1.html
 *
 *  boggle game, 但是呢比如你现在走了一个词apple, 那么a, p, p, l, e这几个char的位置不能继续用了。
 *  于是给你一个board, 一个dict让你计算最多能有多少个valid单词出现在这个Board上面
 *
 * */

/*#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    bool isWord;
    TrieNode* next[26];

    TrieNode(bool isWord = false) {
        this->isWord = isWord;
        memset(next, 0, sizeof(next));
    }
};

class BoggleGame {
public:
    BoggleGame(vector<string>& dictionary) {
        root = new TrieNode();
        buildTrieTree(dictionary);

        for (int i = 0; i < 26; i++) {
            if (root->next[i] != NULL) {
                cout<<"root char:"<<i<<endl;
            }
        }
    }

    vector<string> findMaxCountWords(vector<vector<char>>& board) {
        vector<string> ret;
        if (board.empty() || board[0].empty()) {
            return ret;
        }
        int row = board.size(), col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        vector<string> cur;

        backTrack(board, 0, 0, visited, cur, ret);
        cout<<"after backTrack:"<<ret.size()<<endl;
        return ret;
    }

private:
    void backTrack(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited, vector<string>& cur, vector<string>& ret) {
        int row = board.size(), col = board[0].size();
        if (x == row && y == 0) {
            cout<<"in backTrack, return val"<<endl;
            if (cur.size() > ret.size()) {
                ret = cur;
            }
            return;
        }

        vector<string> pathWords;
        string curWord = "";
        vector<vector<pair<int, int>>> paths;
        vector<pair<int, int>> curPath;
        dfs(board, x, y, visited, curPath, paths, curWord, pathWords, root);

        int nextx = y == col ? x + 1 : x;
        int nexty = y == col ? 0 : y + 1;
        backTrack(board, nextx, nexty, visited, cur, ret);

        for (int i = 0; i < pathWords.size(); i++) {
            cur.push_back(pathWords[i]);
            for (auto p : paths[i]) {
                visited[p.first][p.second] = true;
            }
            backTrack(board, nextx, nexty, visited, cur, ret);
            for (auto p : paths[i]) {
                visited[p.first][p.second] = false;
            }
            cur.pop_back();
        }
    }

    void dfs(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited, vector<pair<int, int>>& curPath,
        vector<vector<pair<int, int>>>& paths, string& curWord, vector<string>& pathWords, TrieNode* node) {
        int row = board.size(), col = board[0].size();
        if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || node->next[board[x][y] - 'a'] == NULL) {
            return;
        }
        node = node->next[board[x][y] - 'a'];
        curWord.push_back(board[x][y]);
        curPath.push_back(make_pair(x, y));

        if (node->isWord) {
            pathWords.push_back(curWord);
            paths.push_back(curPath);
        }

        visited[x][y] = true;
        int direction[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int nextx = x + direction[i][0];
            int nexty = y + direction[i][1];
            dfs(board, nextx, nexty, visited, curPath, paths, curWord, pathWords, node);
        }
        visited[x][y] = false;
        curPath.pop_back();
        curWord.pop_back();
    }

    void buildTrieTree(vector<string>& dictionary) {
        for (auto word : dictionary) {
            cout<<"word:"<<word<<endl;
            insertWord(word);
        }
    }

    void insertWord(string& word) {
        int len = word.length();
        cout<<"insert word:"<<word<<",len:"<<len<<endl;
        TrieNode* p = root;

        for (int i = 0; i < len; i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isWord = true;
        cout<<"insert success, set isWord."<<endl;
    }

    TrieNode* root;
};


int main() {
    vector<vector<char>> board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
    };

    vector<string> dict = {"oath","pea","eat","rain", "ihk", "aa"};
    BoggleGame bg(dict);
    auto result = bg.findMaxCountWords(board);

    for(string s : result) {
        cout << s << endl;
    }

    return 0;
}*/


#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    bool isWord;
    TrieNode* next[26];

    TrieNode(bool isWord = false) {
        this->isWord = isWord;
        memset(next, 0, sizeof(next));
    }
};

class BoggleGame {
public:
    BoggleGame(vector<string>& dict) {
        root = new TrieNode();
        buildTrieTree(dict);
    }

    vector<string> findMaxWords(vector<vector<char>>& board) {
        vector<string> ret;
        if (board.empty() || board[0].empty()) {
            return ret;
        }

        int row = board.size(), col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        vector<string> curResult;

        backTrack(board, 0, 0, visited, curResult, ret);
        return ret;
    }

    void backTrack(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited, vector<string>& curResult, vector<string>& retResult) {
        int row = board.size(), col = board[0].size();
        if (x == row && y == 0) {
            if (curResult.size() > retResult.size()) {
                retResult = curResult;
            }
            return;
        }

        vector<string> result;
        string curWord;
        vector<vector<pair<int, int>>> paths;
        vector<pair<int, int>> curPath;
        dfs(board, x, y, visited, curPath, paths, curWord, result, root);

        int nextx = y == col ? x + 1 : x;
        int nexty = y == col ? 0 : y + 1;
        backTrack(board, nextx, nexty, visited, curResult, retResult);

        int size = result.size();
        for (int i = 0; i < size; i++) {
            curResult.push_back(result[i]);
            vector<pair<int, int>> p = paths[i];
            for (auto item : p) {
                visited[item.first][item.second] = true;
            }
            backTrack(board, nextx, nexty, visited, curResult, retResult);
            for (auto item : p) {
                visited[item.first][item.second] = false;
            }
            curResult.pop_back();
        }
    }

    void dfs(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited, vector<pair<int, int>>& curPath,
            vector<vector<pair<int, int>>>& paths, string& curWord, vector<string>& ret, TrieNode* node) {
        int row = board.size(), col = board[0].size();
        if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || node->next[board[x][y] - 'a'] == NULL) {
            return;
        }

        visited[x][y] = true;
        curWord.push_back(board[x][y]);
        curPath.push_back(make_pair(x, y));
        node = node->next[board[x][y] - 'a'];

        if (node->isWord) {
            ret.push_back(curWord);
            paths.push_back(curPath);
        }

        dfs(board, x - 1, y, visited, curPath, paths, curWord, ret, node);
        dfs(board, x + 1, y, visited, curPath, paths, curWord, ret, node);
        dfs(board, x, y - 1, visited, curPath, paths, curWord, ret, node);
        dfs(board, x, y + 1, visited, curPath, paths, curWord, ret, node);

        curPath.pop_back();
        curWord.pop_back();
        visited[x][y] = false;
    }

private:
    void buildTrieTree(vector<string>& dict) {
        for (auto word : dict) {
            insertWord(word);
        }
    }

    void insertWord(string& word) {
        int len = word.length();
        TrieNode* p = root;

        for (int i = 0; i < len; i++) {
            if (p->next[word[i] - 'a'] == NULL) {
                p->next[word[i] - 'a'] = new TrieNode();
            }
            p = p->next[word[i] - 'a'];
        }
        p->isWord = true;
    }

    TrieNode* root;
};

int main() {
    vector<vector<char>> board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
    };

    vector<string> dict = {"oath","pea","eat","rain", "ihk", "aa"};
    BoggleGame bg(dict);
    auto result = bg.findMaxWords(board);

    for(string s : result) {
        cout << s << endl;
    }

    return 0;
}