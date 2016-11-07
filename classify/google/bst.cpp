//
// Created by ChenMin on 9/30/16.
//
/*
 * User, {id, score}
 * addUser(id, score)
 * findByRank(k)
 * */
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int score, leftCount, rightCount;
    unordered_set<int> ids;//binary search tree, rank by score, store the ids with the same score
    TreeNode *left, *right;
    TreeNode(int id, int score) : leftCount(0), rightCount(0), left(NULL), right(NULL) {
        ids.insert(id);
        this->score = score;
    }
};

class User {
public:
    User() {
        root = NULL;
    }

    int addUser(int id, int score) {
//        if (root == NULL) {
//            root = new TreeNode(id, score);
//            id2score[id] = score;
//            return 1;//only one node, the first one
//        }
        return bstInsert(root, id, score);
    }

    int findByRank(int k) {
        //invalid k
        if (k <= 0 || k > ((root->ids).size() + root->leftCount + root->rightCount)) {
            return -1;
        }
        return search(root, k);
    }
private:
    int search(TreeNode* node, int k) {
        int upper = ((node->ids).size()) + (node->rightCount);
        if (k <= node->rightCount) {
            return search(node->right, k);
        } else if (k <= upper) {
            return *node->ids.begin();
        } else {
            return search(node->left, k - upper);
        }
    }

    int bstInsert(TreeNode* node, int id, int score) {
        if (id2score.count(id)) {
            int oldScore = id2score[id];

            TreeNode* p = node;
            while (p) {
                if (oldScore == p->score) {
                    break;
                } else if (oldScore > p->score) {
                    p = p->right;
                } else {
                    p = p->left;
                }
            }

            if (oldScore == score) {
                return 1 + p->rightCount;
            } else {
                id2score.erase(id);
                if ((p->ids).size() > 1) {
                    p->ids.erase(id);
                    return bstInsert(root, id, score);
                } else {
                    deleteNode(p);
                    return bstInsert(root, id, score);
                }
            }
        } else {
            id2score[id] = score;
            if (node == NULL) {
                root = new TreeNode(id, score);
                return 1;
            }
            if (score == node->score) {
                node->ids.insert(id);
                return *node->ids.begin();
            } else if (score > node->score) {//>
                node->rightCount++;
                if (node->right == NULL) {
                    node->right = new TreeNode(id, score);
                    return 1;
                } else {
                    return bstInsert(node->right, id, score);
                }
            } else {//<
                node->leftCount++;
                if (node->left == NULL) {
                    node->left = new TreeNode(id, score);
                    return ((node->ids).size() + node->rightCount + 1);
                } else {
                    return bstInsert(node->left, id, score);
                }
            }
        }
    }

    void deleteNode(TreeNode* node) {
        TreeNode* par = NULL;
        TreeNode* p = root;
        int score = node->score;

        while (p) {
            if (p->score == score) {
                break;
            } else if (score > p->score) {
                p->rightCount--;
                par = p;
                p = p->right;
            } else {
                p->leftCount--;
                par = p;
                p = p->left;
            }
        }

        if (p ->left == NULL && p->right == NULL) {//case 1, no child
            if (par == NULL) {
                root = NULL;
            } else {
                if (p == par->left) {
                    par->left = NULL;
                } else {
                    par->right = NULL;
                }
            }
        } else if (p->left == NULL) {//case 2, one child
            if (par == NULL) {
                root = p->right;
            } else {
                if (p == par->left) {
                    par->left = p->right;
                } else {
                    par->right = p->right;
                }
            }
        } else if (p->right == NULL) {//case 2, one child
            if (par == NULL) {
                root = p->left;
            } else if (p == par->left) {
                par->left = p->left;
            } else {
                p->right = p->left;
            }
        } else {//case 3, two children
            //replace the current node with the smallest one in the right subtree, update the leftCount, rightCount
            TreeNode* leftMost = p->right;
            while (leftMost->left) {//find the left most node
                leftMost = leftMost->left;
            }
            p->ids = leftMost->ids;
            p->rightCount = ((p->right)->leftCount - (leftMost->ids.size())) + (p->right->rightCount) + ((p->right)->ids).size();
            p->score = leftMost->score;

            //update leftCount, rightCount
            if (p->right->left == NULL) {
                p->right = p->right->right;
            } else {
                TreeNode* cur = p->right;
                TreeNode* curPar = NULL;
                while (cur->left) {
                    cur->leftCount -= (leftMost->ids).size();
                    curPar = cur;
                    cur = cur->left;
                }
                if (cur->right) {
                    curPar->left = cur->right;
                }
            }
        }
    }

    TreeNode* root;
    unordered_map<int, int> id2score;
};
