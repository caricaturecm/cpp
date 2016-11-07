//
// Created by ChenMin on 10/25/16.
//
/*
 *
 * http://www.1point3acres.com/bbs/thread-177167-1-1.html
 *
 * linkedlist,找出最大的两个, 然后swap，不是swap value，swap reference
 * */

/*
 * 大文件排序
 *
 * 外排， k lists each with length N, running time is Nklgk
 * 先根据你的内存将大文件分段，比如：
你的可用内存有1GB，那么就要将大文件分成
1TB / 1GB = 1000段

然后将每段依次读入内存，在内存中使用内部排序算法(例如快速排序，堆排序等)将其排好序，然后将其输出成各个分段文件，例如：
file1，file2，...，file1000

然后对这一千个分段文件的文件头(或文件指针)，建立一颗败者树，用来选取当前最小的元素(或最大的元素，依你的排序要求而定)
并将这最小的元素输出到最终的输出文件里。
重复这一过程，直到1000个分段文件全部被输出。删去这1000个分段文件，仅保留最终的输出文件，即得到排好序的文件。

作者：Kouei
链接：https://www.zhihu.com/question/42007146/answer/97064000
来源：知乎
著作权归作者所有，转载请联系作者获得授权。
 * */


#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int v) : val(v), next(NULL) {}
};

/*ListNode* swapTwo(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    ListNode *maxPos = NULL, *secMaxPos = NULL;
    if (head->val > head->next->val) {
        secMaxPos = head;
    } else {
        maxPos = head;
    }

    ListNode* cur = head->next;
    while (cur->next) {
        if (maxPos == NULL) {
            if (cur->next->val > head->val) {
                secMaxPos = NULL;
                maxPos = cur;
            } else if (cur->next->val > secMaxPos->val) {
                secMaxPos = cur;
            }
        } else if (secMaxPos == NULL) {
            if (cur->next->val > maxPos->next->val) {
                secMaxPos = maxPos;
                maxPos = cur;
            } else if (cur->next->val > head->val) {
                secMaxPos = cur;
            }
        } else {
            if (cur->next->val > maxPos->next->val) {
                secMaxPos = maxPos;
                maxPos = cur;
            } else if (cur->next->val > secMaxPos->next->val) {
                secMaxPos = cur;
            }
        }
        cur = cur->next;
    }

    if (maxPos == NULL) {

    }
}*/

ListNode* swapTwowithDummy(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *maxPos, *secMaxPos;

    if (head->val > head->next->val) {
        maxPos = dummy;
        secMaxPos = head;
    } else {
        maxPos = head;
        secMaxPos = dummy;
    }

    ListNode *cur = head->next;
    while (cur->next) {
        if (cur->next->val > maxPos->next->val) {
            secMaxPos = maxPos;
            maxPos = cur;
        } else if (cur->next->val > secMaxPos->next->val) {
            secMaxPos = cur;
        }
        cur = cur->next;
    }

    if (maxPos->next == secMaxPos) {
        ListNode* tmp = secMaxPos->next->next;
        maxPos->next = secMaxPos->next;
        maxPos->next->next = secMaxPos;
        secMaxPos->next = tmp;
    } else if (secMaxPos->next == maxPos) {
        cout<<"sec next is max"<<endl;
        ListNode* tmp = maxPos->next->next;
        secMaxPos->next = maxPos->next;
        secMaxPos->next->next = maxPos;
        maxPos->next = tmp;
    } else {
        ListNode *next1 = maxPos->next->next;
        ListNode *next2 = secMaxPos->next->next;
        ListNode *tmp = maxPos->next;
        maxPos->next = secMaxPos->next;
        secMaxPos->next = tmp;
        maxPos->next->next = next1;
        secMaxPos->next->next = next2;
    }

    return dummy->next;
}

int main() {
    ListNode* head = new ListNode(6);
    ListNode* n1 = new ListNode(5);
    head->next = n1;

    ListNode* n2 = new ListNode(4);
    n1->next = n2;

    ListNode* n3 = new ListNode(2);
    n2->next = n3;

    ListNode* n4 = new ListNode(8);
    n3->next = n4;

    head = swapTwowithDummy(head);
    ListNode* cur = head;
    while (cur) {
        cout<<cur->val<<" ";
        cur = cur->next;
    }
    cout<<endl;
}



