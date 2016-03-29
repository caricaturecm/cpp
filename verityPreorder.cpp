//255. Verify Preorder Sequence in Binary Search Tree
/*
 * The property of bst
 * use a stack
 * when encounter a ascending number, which means arrive the right subtree, then pop the left subtree
 *
 * Can also abusing the vector to instead of the stack
 * */
class Solution {
    public:
        bool verifyPreorder(vector<int>& preorder) {
            stack<int> s;

            int min = INT_MIN;
            for (auto num : preorder) {
                if (num < min) {
                    return false;
                }
                while (!s.empty() && num > s.top()) {
                    min = s.top();
                    s.pop();
                }
                s.push(num);
            }
            return true;
        }
};
