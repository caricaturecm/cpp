//99. Recover Binary Search Tree
class Solution {
    public:
        void recoverTree(TreeNode* root) {
            pre = new TreeNode(INT_MIN);
            first = NULL;
            sec = NULL;
            inorder(root);
            swap(first->val, sec->val);
        }

    private:
        void inorder(TreeNode* root) {
            if (root == NULL) {
                return;
            }
            inorder(root->left);
            //first index,
            if (first == NULL && root->val <= pre->val) {
                first = pre;
            }
            //second index, maybe consecutive with the first index, or not
            if (first != NULL && root->val <= pre->val) {
                sec = root;
            }
            pre = root;
            inorder(root->right);
        }

        TreeNode *first, *sec, *pre;
};
