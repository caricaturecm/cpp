//124. Binary Tree Maximum Path Sum
/*
 * This is really clever
 * The maximum path sum in current TreeNode* root, may come from the left subtree, right subtree, or the path through
 * the root
 *
 * The alg compute the maximum path in every node (contain the val of current root node), from the current root to one
 * of its leaf node in current subtree
 * 
 * And update the max path sum at current node
 *
 * */
class Solution {
    public:
        int maxPathSum(TreeNode* root) {
            int maxPath = INT_MIN;
            maxFromRoot(root, maxPath);
            return maxPath;
        }

    private:
        int maxFromRoot(TreeNode* root, int& maxPath) {
            if (root == NULL) {
                return 0;
            }
            int lMax = maxFromRoot(root->left, maxPath);
            int rMax = maxFromRoot(root->right, maxPath);
            if (lMax < 0) {
                lMax = 0;
            }
            if (rMax < 0) {
                rMax = 0;
            }
            if (lMax + rMax + root->val > maxPath) {
                maxPath = lMax + rMax + root->val;
            }

            return root->val + max(lMax, rMax);
        }
};
