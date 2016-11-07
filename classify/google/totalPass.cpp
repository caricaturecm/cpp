/*
 * totalpass of an element x in an array, means the number of elements in the array larger than x,
 * find the maximum totalpass in the array
 *
 * left pass, the numbers in the left are larger, LC315
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val, rightCount, copyCount;
    TreeNode *left, *right;

    TreeNode(int v) : val(v), rightCount(0), copyCount(1), left(NULL), right(NULL) {}
};

class Pass {
public:
    int totalPass(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int size = nums.size(), minVal = nums[0];
        for (int i = 1; i < size; i++) {
            minVal = min(minVal, nums[i]);
        }
        int count = 0;
        for (auto num : nums) {
            if (num > minVal) {
                count++;
            }
        }
        return count;
    }

    vector<int> leftPass(vector<int>& nums) {
        vector<int> ret;
        if (nums.empty()) {
            return ret;
        }
        int size = nums.size();
        root = new TreeNode(nums[0]);
        ret.push_back(0);
        for (int i = 1; i < size; i++) {
            ret.push_back(insert(root, nums[i]));
        }
        return ret;
    }

private:
    int insert(TreeNode* node, int val) {
        int ret;
        if (val == node->val) {
            node->copyCount++;
            ret = node->rightCount;
        } else if (val > node->val) {
            node->rightCount++;
            if (node->right == NULL) {
                node->right = new TreeNode(val);
                ret = 0;
            } else {
                ret = insert(node->right, val);
            }
        } else {//<
            if (node->left == NULL) {
                node->left = new TreeNode(val);
                ret = node->copyCount + node->rightCount;
            } else {
                ret = node->copyCount + node->rightCount + insert(node->left, val);
            }
        }

        return ret;
    }

    TreeNode* root;
};



int main() {
    Pass pass;
    int nums[] = {1, 2, 1};
    vector<int> vnums(nums, nums + sizeof(nums) / sizeof(int));
    int count = pass.totalPass(vnums);
    cout<<"count:"<<count<<endl;

    int a[] = {5, 2, 6, 1, 1, 2, 6, 2};
    vnums.assign(a, a + sizeof(a) / sizeof(int));
    vector<int> ret = pass.leftPass(vnums);
    for (auto num : ret) {
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}