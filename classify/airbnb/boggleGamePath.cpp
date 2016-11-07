//
// Created by ChenMin on 11/3/16.
//

/*
 *
 * 题目是给定一个2d matrix of letters和一个dictionary，找出一条path包含最多的存在于字典的word个数 讨论了半天算法，
 * 真到写code的时候时间就来不及了，test case没来得及写，也没来得及优化
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

class BoggleGamePath {
public:
    BoggleGamePath(vector<string>& dict) {
        root = new TrieNode();
        buildTrieTree(dict);
    }

    vector<string> findMaxPath(vector<vector<char>>& board) {
        vector<string> ret;
        if (board.empty() || board[0].empty()) {
            return ret;
        }
        int row = board.size(), col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        vector<string> cur;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                dfs(board, i, j, visited, cur, ret, "", root);
            }
        }

        return ret;
    }

private:
    void dfs(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited,
             vector<string>& cur, vector<string>& ret, string curWord, TrieNode* node) {

        int row = board.size(), col = board[0].size();
        if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || node->next[board[x][y] - 'a'] == NULL) {
            return;
        }

        node = node->next[board[x][y] - 'a'];
        curWord.push_back(board[x][y]);

        visited[x][y] = true;
        int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        if (node->isWord) {
            cur.push_back(curWord);//push it
            if (cur.size() > ret.size()) {
                ret = cur;
            }

            for (int i = 0; i < 4; i++) {
                int nextx = x + direction[i][0];
                int nexty = y + direction[i][1];
                dfs(board, nextx, nexty, visited, cur, ret, "", root);
            }
            cur.pop_back();
        }

        for (int i = 0; i < 4; i++) {
            int nextx = x + direction[i][0];
            int nexty = y + direction[i][1];
            dfs(board, nextx, nexty, visited, cur, ret, curWord, node);
        }
        visited[x][y] = false;
    }

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

    vector<string> dict = {"oath","klv", "an", "aer", "oat"};
    BoggleGamePath bg(dict);
    auto result = bg.findMaxPath(board);

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

class BoggleGamePath {
public:
    BoggleGamePath(vector<string>& dict) {
        root = new TrieNode();
        buildTrieTree(dict);
    }

    vector<string> findMaxWordPath(vector<vector<char>>& board) {
        vector<string> ret;
        if (board.empty() || board[0].empty()) {
            return ret;
        }

        int row = board.size(), col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        vector<string> cur;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                dfs(board, i, j, visited, cur, "", ret, root);
            }
        }
        return ret;
    }

private:
    void dfs(vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited,
             vector<string>& cur, string curWord, vector<string>& ret, TrieNode* node) {
        int row = board.size(), col = board[0].size();
        if (x < 0 || x >= row || y < 0 || y >= col || visited[x][y] || node->next[board[x][y] - 'a'] == NULL) {
            return;
        }

        node = node->next[board[x][y] - 'a'];
        curWord.push_back(board[x][y]);
        int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        visited[x][y] = true;

        if (node->isWord) {
            cur.push_back(curWord);
            if (cur.size() > ret.size()) {
                ret = cur;
            }

            for (int i = 0; i < 4; i++) {
                int nextx = x + direction[i][0];
                int nexty = y + direction[i][1];
                dfs(board, nextx, nexty, visited, cur, "", ret, root);
            }
            cur.pop_back();
        }

        for (int i = 0; i < 4; i++) {
            int nextx = x + direction[i][0];
            int nexty = y + direction[i][1];
            dfs(board, nextx, nexty, visited, cur, curWord, ret, node);
        }
        visited[x][y] = false;
    }

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

    vector<string> dict = {"oath","klv", "an", "aer", "oat"};
    BoggleGamePath bg(dict);
    auto result = bg.findMaxWordPath(board);

    for(string s : result) {
        cout << s << endl;
    }

    return 0;
}