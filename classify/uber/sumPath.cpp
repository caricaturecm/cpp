//
// Created by ChenMin on 10/1/16.
//

/*
 * 一个二叉树，定义从某一个节点到 到他的某个孩子之间的所有节点为一个path。
输入颗二叉树，给定一个值t。 求所有和为t的path
 * */

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class SumPath {
public:
    SumPath(int sum) : initialSum(sum) {}

    vector<vector<int>> getPath(TreeNode* root, int sum) {
        helper(root, sum);
        return finalRet;
    }
private:
    vector<vector<int>> helper(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        if (root == NULL) {
            return ret;
        }
        if (root->val == sum) {//only one node,
            vector<int> curPath(1, root->val);
            ret.push_back(curPath);
        }
        vector<vector<int>> leftPath = helper(root->left, sum - root->val);// the left path, contain current node
        vector<vector<int>> rightPath = helper(root->right, sum - root->val);//the right path,

        for (auto path : leftPath) {
            vector<int> curPath(1, root->val);
            curPath.insert(curPath.end(), path.begin(), path.end());
            ret.push_back(curPath);
        }
        for (auto path : rightPath) {
            vector<int> curPath(1, root->val);
            curPath.insert(curPath.end(), path.begin(), path.end());
            ret.push_back(curPath);
        }
        if (initialSum == sum) {
            finalRet.insert(finalRet.end(), ret.begin(), ret.end());
        }

        return ret;
    }

    vector<vector<int>> finalRet;
    int initialSum;
};

int main() {
    TreeNode* root = new TreeNode(0);

    TreeNode* v1 = new TreeNode(-1);
    TreeNode* v2 = new TreeNode(1);
    root->left = v1;
    root->right = v2;

    TreeNode* v3 = new TreeNode(3);
    TreeNode* v4 = new TreeNode(2);
    TreeNode* v5 = new TreeNode(2);

    v1->left = v3;
    v1->right = v4;
    v2->right = v5;

    TreeNode* v6 = new TreeNode(-1);
    TreeNode* v7 = new TreeNode(1);
    TreeNode* v8 = new TreeNode(-3);
    TreeNode* v9 = new TreeNode(1);

    v3->left = v6;
    v4->right = v7;
    v5->left = v8;
    v5->right = v9;

    TreeNode* v10 = new TreeNode(-1);
    v6->right = v10;

    TreeNode* v11 = new TreeNode(0);
    TreeNode* v12 = new TreeNode(3);
    v10->left = v11;
    v10->right = v12;

    SumPath sp(0);
    vector<vector<int>> pathes = sp.getPath(root, 0);
    for (auto path : pathes) {
        for (auto node : path) {
            cout<<node<<" ";
        }
        cout<<endl;
    }
    return 0;
}


