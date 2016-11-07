//
// Created by ChenMin on 10/3/16.
//

/*Input:
 * a double linked list
 * an array, contains some nodes in the double linked list
 *
 * Output:
 * how many segements, the array split the double linked list
 * */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Node {
    int val;
    Node *pre, *next;
    Node(int v) : val(v) , pre(NULL), next(NULL) {}
};

class Solution {
public:
    int getNumber(Node* head, vector<Node*>& nodes) {
        int size = nodes.size();
        int count = size;//every node is an isolate segment at the beginning
        unordered_set<Node*> visitedNodes;
        for (int i = 0; i < size; i++) {
            if (visitedNodes.count(nodes[i]->pre) || visitedNodes.count(nodes[i]->next)) {
                count--;
            }
            if (visitedNodes.count(nodes[i]->pre) && visitedNodes.count(nodes[i]->next)) {
                count--;
            }
            visitedNodes.insert(nodes[i]);
        }
        return count;
    }
};

int main() {
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);

    head->next = n2;
    n2->pre = head;
    n2->next = n3;

    n3->pre = n2;
    n3->next = n4;

    n4->pre = n3;
    n4->next = n5;

    n5->pre = n4;
    n5->next = n6;

    n6->pre = n5;
    n6->next = n7;

    n7->pre = n6;

    Solution sol;
    vector<Node*> nodes;
    nodes.push_back(head);
    nodes.push_back(n4);
    nodes.push_back(n3);
    nodes.push_back(n6);
    nodes.push_back(n2);
    nodes.push_back(n7);
    nodes.push_back(n5);
    int ret = sol.getNumber(head, nodes);
    cout<<"ret:"<<ret<<endl;
    return 0;
}

