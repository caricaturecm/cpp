//
// Created by ChenMin on 10/10/16.
//
/*
 * TimeTravelingHashTable
 * insert(key, value, timestamp)
 * get(key, timestamp)
 * get(key) // returns value associated with key at latest time
 * */
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

class TimeTravelingHashTable {
public:
    void insert(int key, int value, int timestamp) {
        table[key][timestamp] = value;
    }

    int get(int key, int timestamp) {
        if (table.count(key) == 0) {
            return INT_MIN;
        }
        int ret;
        if (table[key].count(timestamp)) {
            ret = table[key][timestamp];
        } else {
            auto it = table[key].lower_bound(timestamp);
            if (it == table[key].begin()) {//has no value at this timestamp yet
                ret = INT_MIN;
            } else {
                --it;
                ret = it->second;
            }
        }
        return ret;
    }

    int get(int key) {
        if (table.count(key) == 0) {
            return INT_MIN;
        }
        return table[key].rbegin()->second;
    }
private:
    unordered_map<int, map<int, int>> table;
};

int main() {
    TimeTravelingHashTable ins;
    ins.insert(1, 1, 10);
    cout<<ins.get(1)<<endl;
    cout<<ins.get(1, 11)<<endl;
    ins.insert(1, 2, 20);
    cout<<ins.get(1, 15)<<endl;
    cout<<ins.get(1, 11)<<endl;
    cout<<ins.get(1, 21)<<endl;
    cout<<ins.get(1)<<endl;
    return 0;
}