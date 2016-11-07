//
// Created by ChenMin on 10/11/16.
//
/*
 * http://www.1point3acres.com/bbs/thread-193460-1-1.html
 *
 * BST insert, delete
 * */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class BST {
public:
    TreeNode* search(int val) {
        TreeNode* cur = root;

        while (cur) {
            if (cur->val == val) {
                return cur;
            } else if (val > cur->val) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return NULL;
    }

    TreeNode* insert(int val) {
        TreeNode* node = new TreeNode(val);
        if (root == NULL) {
            root = node;
            return node;
        }
        TreeNode *par = NULL, *cur = root;
        while (cur) {
            if (val == cur->val) {//no duplicate in bst
                return NULL;
            } else if (val > cur->val) {
                par = cur;
                cur = cur->right;
            } else {
                par = cur;
                cur = cur->left;
            }
        }
        if (val > par->val) {
            par->right = node;
        } else {
            par->left = node;
        }
        return node;
    }

    void deleteNode(TreeNode* node) {
        TreeNode *par = NULL, *cur = root;
        while (cur) {
            if (cur->val == node->val) {
                break;
            } else if (node->val > cur->val) {
                par = cur;
                cur = cur->right;
            } else {
                par = cur;
                cur = cur->left;
            }
        }

        if (node->left == NULL && node->right == NULL) {//case 1, no child
            if (par == NULL) {//node is the root
                root = NULL;
            } else {
                if (node == par->left) {
                    par->left = NULL;
                } else {
                    par->right = NULL;
                }
            }
        } else if (node->left == NULL) {//case 2, one child, right
            if (par == NULL) {
                root = node->right;
            } else {
                if (node == par->left) {
                    par->left = node->right;
                } else {
                    par->right = node->right;
                }
            }
        } else if (node->right == NULL) {//case 2, one child, left
            if (par == NULL) {
                root = node->left;
            } else {
                if (node == par->left) {
                    par->left = node->left;
                } else {
                    par->right = node->left;
                }
            }
        } else {//two child
            //replace the current node with the smallest one in the right subtree, and remove the smallest one
            TreeNode* leftMost = node->right;
            while (leftMost->left) {
                par = leftMost;
                leftMost = leftMost->left;
            }
            node->val = leftMost->val;

            if (node->right->left == NULL) {
                node->right = node->right->right;
            } else {
                par->left = leftMost->right;
            }
        }
    }

    vector<int> inorder() {
        vector<int> nums;
        stack<TreeNode*> s;
        TreeNode* cur = root;

        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        while (!s.empty()) {
            cur = s.top();
            s.pop();
            nums.push_back(cur->val);
            cur = cur->right;
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
        }
        return nums;
    }
private:
    TreeNode* root;
};


int main() {
    BST bst;
    bst.insert(9);
    bst.insert(0);
    bst.insert(8);
    bst.insert(3);
    bst.insert(12);
    bst.insert(10);
    bst.insert(18);

    TreeNode* node = bst.search(9);
    if (node != NULL) {
        cout<<"del node:"<<node->val<<endl;
        bst.deleteNode(node);
    }

    vector<int> nums = bst.inorder();
    for (auto num : nums) {
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}