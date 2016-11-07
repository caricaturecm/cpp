//
// Created by ChenMin on 10/14/16.
//

/*
 *https://instant.1point3acres.com/thread/189483
 *
 * 在文件夹下找出所有包涵电话号码的文件 (grep 和 regular expression)

 grep -rn '^((\+1) | (1)) ? \d{10}' *
 * */

/*
 * https://instant.1point3acres.com/thread/168017
 *
 *huffman coding的题目，input是一个array，element是{integer: frequency}，求出它们的huffman code.
 * */
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    int num;
    float frequency;
    TreeNode *left, *right;

    TreeNode(int v, float f) : num(v), frequency(f), left(NULL), right(NULL) {}
};

struct mycmp {
    bool operator()(TreeNode* a, TreeNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCode {
public:
    TreeNode* huffmanTree(vector<pair<int, float>>& num2frequency) {
        priority_queue<TreeNode*, vector<TreeNode*>, mycmp> nodes;
        for (auto item : num2frequency) {
            nodes.push(new TreeNode(item.first, item.second));
        }

        while (nodes.size() > 1) {
            TreeNode* first = nodes.top();
            nodes.pop();
            TreeNode* sec = nodes.top();
            nodes.pop();
            TreeNode* par = new TreeNode(-1, first->frequency + sec->frequency);
            par->left = first;
            par->right = sec;
            nodes.push(par);
        }
        return nodes.top();
    }

    void inorder(TreeNode* root) {
        TreeNode* p = root;
        stack<TreeNode*> s;
        while (p) {
            s.push(p);
            p = p->left;
        }

        while (!s.empty()) {
            p = s.top();
            s.pop();
            if (p->right == NULL) {
                cout<<"p->val:"<<p->num<<",fre:"<<p->frequency<<endl;
            } else {
                p = p->right;
                while (p) {
                    s.push(p);
                    p = p->left;
                }
            }
        }
    }
};

int main() {
    vector<pair<int, float>> nums;
    nums.push_back(make_pair(1, 0.2));
    nums.push_back(make_pair(2, 0.26));
    nums.push_back(make_pair(3, 0.13));
    nums.push_back(make_pair(4, 0.13));
    nums.push_back(make_pair(5, 0.13));
    nums.push_back(make_pair(6, 0.07));
    nums.push_back(make_pair(7, 0.07));

    HuffmanCode huff;
    TreeNode* root = huff.huffmanTree(nums);

    huff.inorder(root);
    return 0;
}