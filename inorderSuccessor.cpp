//285. Inorder Successor in BST
/*
 * Actually, find p in the left subtree or right subtree
 *
 * if in the left subtree, then the successor can be in the leftsubtree or be the root
 *
 * if p is in the right subtree, then the successor can only in the rightsubtree or NULL
 * */
class Solution {
    public:
        TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
            if (root == NULL || p == NULL) {
                return NULL;
            }
            if (p->val >= root->val) {
                return inorderSuccessor(root->right, p);
            } else {
                TreeNode* left = inorderSuccessor(root->left, p);
                return left == NULL ? root : left;
            }
        }
};
