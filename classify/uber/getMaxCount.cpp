//
// Created by ChenMin on 10/11/16.
//
/*
 * 题目大致意思是：实现三个function， void addKey(String key) ; int getCountForKey(String key) ；String getKeyWithMaxCount().
 *
 * follow up，添加一个function：void decrementKey（String key）
 * */
#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
using namespace std;


class Solution {
public:
    Solution() {
        maxCount = 0;
    }

    void addKey(string key) {
        keyCount[key]++;
        if (keyCount[key] > maxCount) {
            maxCount = keyCount[key];
            keyWithMaxCount = key;
        }
    }

    int getCountForKey(string key) {
        return keyCount[key];
    }

    string getKeyWithMaxCount() {
        if (maxCount == 0) {
            return "";
        }
        return keyWithMaxCount;
    }

private:
    unordered_map<string, int> keyCount;
    int maxCount;
    string keyWithMaxCount;
};


class DecreaseFunc {
public:
    void addKey(string key) {
        keyCount[key]++;
        int curCount = keyCount[key];
        if (curCount > 1) {
            countKey[curCount - 1].erase(key);
            if (countKey[curCount - 1].empty()) {
                countKey.erase(curCount - 1);
            }
        }
        countKey[curCount].insert(key);
    }

    void decreaseKey(string key) {
        if (keyCount.count(key) == 0) {
            return;
        }
        keyCount[key]--;
        int curCount = keyCount[key];
        countKey[curCount + 1].erase(key);
        if (countKey[curCount + 1].empty()) {
            countKey.erase(curCount + 1);
        }
        if (curCount > 0) {
            countKey[curCount].insert(key);
        }
    }

    int getCountForKey(string key) {
        return keyCount[key];
    }

    string getKeyWithMaxCount() {
        if (countKey.empty()) {
            return "";
        }
        return *(countKey.rbegin()->second).begin();
    }
private:
    unordered_map<string, int> keyCount;
    map<int, unordered_set<string>> countKey;
};

int main() {
    DecreaseFunc sol;
    sol.addKey("a");
    sol.addKey("a");
    sol.addKey("a");
    cout<<"count:"<<sol.getCountForKey("a")<<endl;
    cout<<"max count key:"<<sol.getKeyWithMaxCount()<<endl;
    sol.addKey("b");
    cout<<"count b:"<<sol.getCountForKey("b")<<endl;
    cout<<"count c:"<<sol.getCountForKey("c")<<endl;
    cout<<"max count key:"<<sol.getKeyWithMaxCount()<<endl;

    sol.decreaseKey("a");
    sol.decreaseKey("a");
    cout<<"count a:"<<sol.getCountForKey("a")<<endl;
    cout<<"max count key:"<<sol.getKeyWithMaxCount()<<endl;
    sol.decreaseKey("a");
    cout<<"max count key:"<<sol.getKeyWithMaxCount()<<endl;
    sol.decreaseKey("b");
    cout<<"count a:"<<sol.getCountForKey("a")<<endl;
    cout<<"max count key:"<<sol.getKeyWithMaxCount()<<endl;
    return 0;
}