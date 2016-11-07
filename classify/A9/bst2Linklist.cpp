//
// Created by ChenMin on 10/16/16.
//
/*
 * http://1point3acres.com/bbs/forum.php?mod=viewthread&tid=119591&extra=page%3D5%26filter%3Dsortid%26sortid%3D192%26sortid%3D192&mobile=2
 *
 * 二叉树树in place变链表
 * */
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class Tree {
public:
    TreeNode* bfsLinkedList(TreeNode* root) {
        if (root == NULL) {
            return NULL;
        }
        TreeNode *head = NULL, *pre = NULL;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* cur = q.front();
            q.pop();
            if (cur->left) {
                q.push(cur->left);
            }
            if (cur->right) {
                q.push(cur->right);
            }
            cur->left = NULL;
            cur->right = NULL;
            if (pre == NULL) {
                head = cur;
            } else {
                pre->right = cur;
            }
            pre = cur;
        }
        return head;
    }

    TreeNode* inorderLinkedLitst(TreeNode* root) {
        if (root == NULL) {
            return NULL;
        }
        TreeNode *head = NULL, *pre = NULL;
        TreeNode* cur = root;
        stack<TreeNode*> s;

        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        while (!s.empty()) {
            cur = s.top();
            s.pop();
            TreeNode* p = cur->right;
            while (p) {
                s.push(p);
                p = p->left;
            }
            cur->left = NULL;
            cur->right = NULL;
            if (pre == NULL) {
                head = cur;
            } else {
                pre->right = cur;
            }
            pre = cur;
        }
        return head;
    }
};


int main() {
    TreeNode* root = new TreeNode(5);
    TreeNode* v1 = new TreeNode(3);
    TreeNode* v2 = new TreeNode(8);

    root->left = v1;
    root->right = v2;

    TreeNode* v3 = new TreeNode(2);
    TreeNode* v4 = new TreeNode(4);
    TreeNode* v5 = new TreeNode(7);
    TreeNode* v6 = new TreeNode(9);

    v1->left = v3;
    v1->right = v4;
    v2->left = v5;
    v2->right = v6;

    TreeNode* v7 = new TreeNode(6);
    v5->left = v7;

    Tree tree;
    TreeNode* head;
//    head = tree.bfsLinkedList(root);
//    while (head) {
//        cout<<"val:"<<head->val<<endl;
//        head = head->right;
//    }

    cout<<"inorder traverse:"<<endl;
    head = tree.inorderLinkedLitst(root);
    while (head) {
        cout<<"val:"<<head->val<<endl;
        head = head->right;
    }
}