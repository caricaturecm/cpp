/*
 * a tree, the value of left equals to the right
 * */
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class TreeEqualVal {
public:
    bool isEqual(TreeNode* root) {
        int val = 0;
        return helper(root, val);
    }
private:
    bool helper(TreeNode* root, int& val) {
        if (root == NULL) {
            return true;
        }
        int leftVal = 0;
        bool isLeft = helper(root->left, leftVal);
        if (!isLeft) {
            return false;
        }
        int rightVal = 0;
        bool isRight = helper(root->right, rightVal);
        if (!isRight) {
            return false;
        }
        if (leftVal != rightVal) {
            return false;
        }

        val = leftVal + rightVal + root->val;
        return true;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    TreeNode* v1 = new TreeNode(3);
    TreeNode* v2 = new TreeNode(1);

    root->left = v1;
    root->right = v2;
    TreeNode* v3 = new TreeNode(1);
    v2->left = v3;

    TreeEqualVal ins;
    bool isequal = ins.isEqual(root);
    cout<<"isequal:"<<isequal<<endl;
    return 0;
}