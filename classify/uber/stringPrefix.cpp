//
// Created by ChenMin on 10/11/16.
//
/*
 * 然后给了一个string的list，让给出所有可以成为除自己以外的prefix的string。
 * 例如["a", "ab", "dogcat","dog"]，就返回"a"和"dog"。
 *
 * http://www.1point3acres.com/bbs/thread-193176-1-1.html
 *
 * should solve with trie tree
 * */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct TrieNode {
    bool isWord;
    TrieNode* next[26];

    TrieNode(bool isWord = false) {
        this->isWord = isWord;
        memset(next, 0, sizeof(next));
    }
};
class Prefix{
public:
    Prefix() {
        root = new TrieNode();
    }

    vector<string> triePrefix(vector<string>& words) {
        unordered_set<string> ret;
        for (auto word : words) {
            TrieNode* p = root;
            int len = word.length();
            for (int i = 0; i < len; i++) {
                if (p->next[word[i] - 'a'] != NULL) {
                    if (p->next[word[i] - 'a']->isWord) {
                        ret.insert(word.substr(0, i + 1));
                    }
                } else {
                    p->next[word[i] - 'a'] = new TrieNode();
                }
                p = p->next[word[i] - 'a'];
            }
            for (int i = 0; i < 26; i++) {
                if (p->next[i] != NULL) {
                    ret.insert(word);
                    break;
                }
            }
            p->isWord = true;
        }
        return vector<string>(ret.begin(), ret.end());
    }

    vector<string> prefixWords(vector<string>& words) {
        sort(words.begin(), words.end());
        vector<string> ret;
        int size = words.size();

        for (int i = 0; i < size - 1; i++) {
            if (words[i + 1].length() >= words[i].length() && words[i + 1].substr(0, words[i].length()) == words[i]) {
                ret.push_back(words[i]);
            }
        }
        return ret;
    }
private:
    TrieNode* root;
};


int main() {
    vector<string> words;
    words.push_back("ab");
    words.push_back("a");
    words.push_back("dogcat");
    words.push_back("dog");
    words.push_back("abcd");
    words.push_back("abc");

    Prefix pre;
    vector<string> ret = pre.prefixWords(words);
    for (auto word : ret) {
        cout<<word<<" ";
    }
    cout<<endl;

    ret = pre.triePrefix(words);
    for (auto word : ret) {
        cout<<word<<" ";
    }
    cout<<endl;
    return 0;
}
