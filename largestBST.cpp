//333. Largest BST Subtree
/*
 * Smart alg
 *
 * Recursive, scan the tree bottom up
 * */
class Solution {
    public:
        int largestBSTSubtree(TreeNode* root) {
            int ret = 0;
            int minv, maxv;

            dfs(root, ret, minv, maxv);
            return ret;
        }

    private:
        bool dfs(TreeNode* root, int& ret, int& minv, int& maxv) {
            if (root == NULL) {
                return true;
            }

            int leftSize = 0, rightSize = 0;
            int leftMin, leftMax, rightMin, rightMax;

            int isLeft = dfs(root->left, leftSize, leftMin, leftMax);
            int isRight = dfs(root->right, rightSize, rightMin, rightMax);

            if (isLeft && isRight) {
                if ((root->left == NULL || root->val > leftMax) && (root->right == NULL || root->val < rightMin)) {
                    ret = leftSize + rightSize + 1;
                    minv = root->left ? leftMin : root->val;
                    maxv = root->right ? rightMax : root->val;
                    return true;
                }
            }

            ret = max(leftSize, rightSize);
            return false;
        }
};
