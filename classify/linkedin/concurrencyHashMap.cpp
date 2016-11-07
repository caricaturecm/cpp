//
// Created by ChenMin on 10/18/16.
//

/*
 * Implement a concurrency HashMap
 * */
#include <iostream>
#include <vector>
using namespace std;

//template<class K, class V>
//struct HashNode {
//    K key;
//    V value;
//    HashNode* next;
//
//    HashNode(K k, V val) : key(k), value(val), next(NULL) {}
//};
typedef unsigned long(*GetKeyValue)(const string& );

template<class K, class V, class FuncType>
class HashMap {
public:
    HashMap(FuncType func, const V& _null);
    ~HashMap() {};
    V getVal(const K& key);
    V delVal(const K& key);
//    V putVal(const HashNode<K, V>& hashNode);
    void putVal(const K& key, const V& val);

private:
    vector<vector<pair<K, V>>> table;
    unsigned long capacity;
    FuncType HashCode;
    const V NULL_VAL;
};

template<class K, class V, class FuncType>
HashMap<K, V, FuncType>::HashMap(FuncType func, const V& _null) : NULL_VAL(_null) {
    capacity = 100;
    HashCode = func;
    table.assign(capacity, vector<pair<K, V>>());
};

template<class K, class V, class FuncType>
V HashMap<K, V, FuncType>::delVal(const K& key) {
    int index = HashCode(key);
    index %= capacity;
    if (table[index].empty()) {
        return NULL_VAL;
    } else {
        vector<pair<K, V>> valList = table[index];
        bool exist = false;
        V val;
        for (auto it = valList.begin(); it != valList.end(); it++) {
            if (it->first == key) {
                val = it->second;
                valList.erase(it);
                exist = true;
                break;
            }
        }
        table[index] = valList;
        if (exist) {
            return val;
        }
    }
    return NULL_VAL;
};

template<class K, class V, class FuncType>
void HashMap<K, V, FuncType>::putVal(const K& key, const V& val) {
    unsigned long index = HashCode(key);
    index %= capacity;
    if (table[index].empty()) {
        table[index].push_back(make_pair(key, val));
    } else {
        vector<pair<K, V>> valList = table[index];
        bool exist = false;
        for (auto node : valList) {
            if (node.first == key) {
                node.second = val;
                exist = true;
                break;
            }
        }
        if (!exist) {
            table[index].push_back(make_pair(key, val));
        }
    }
}

template<class K, class V, class FuncType>
V HashMap<K, V, FuncType>::getVal(const K &key) {
    unsigned long index = HashCode(key);
    index %= capacity;
    if (table[index].empty()) {
        return NULL_VAL;
    } else {
        vector<pair<K, V>> valList = table[index];
        for (auto node : valList) {
            if (node.first == key) {
                return node.second;
            }
        }
    }
    return NULL_VAL;
}

unsigned long GetHashValue_imp(const string& str) {
    long hashVal = 0;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        hashVal = hashVal * 31 + (unsigned long)(str[i]);
    }
    return hashVal;
}

int main() {
    HashMap<string, string, GetKeyValue> hmap(GetHashValue_imp, "NULL");
    hmap.putVal("1", "1");
    string val = hmap.getVal("1");
    cout<<"val:"<<val<<endl;
    hmap.delVal("1");
    cout<<"after del:"<<hmap.getVal("1")<<endl;
    return 0;
}