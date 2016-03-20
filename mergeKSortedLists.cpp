/*
 * The recursive alg to merge two sorted list
 *
 * the time complexity of merge k sorted list is knlgk, assume every list with size n
 * just like the merge sort n nums, the time complexity is nlgn
 *
 * The time complexit is k/2*(2n) + k/4*(4n) + k/8*(8n) + ... + (k/2^lgk) *(n*2^lgk)
 *
 * */
class Solution {
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            if (lists.empty()) {
                return NULL;
            }
            //erase the begin of a vector is inefficient, so use this trick alg here
            int size = lists.size();
            while (size > 1) {
                for (int i = 0; i < size / 2; i++) {
                    lists[i] = merge(lists[i], lists[size -i - 1]);
                }
                size = (size + 1) / 2;
            }
            return lists[0];
        }

    private:
        ListNode* merge(ListNode* l1, ListNode* l2) {
            if (l1 == NULL) {
                return l2;
            }
            if (l2 == NULL) {
                return l1;
            }

            if (l1->val <= l2->val) {
                l1->next = merge(l1->next, l2);
                return l1;
            } else {
                l2->next = merge(l1, l2->next);
                return l2;
            }
        }
};
