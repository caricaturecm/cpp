#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdlib.h>//rand()
#include <algorithm>//swap()
using namespace std;

/*
 * Data structure that add(num), remove(num), randomRemove() all are in O(1)
 * */
class ConstAccess {
public:
    void add(int num) {
        if (m.find(num) != m.end()) {//exist in the array, no duplicate
            return;
        }
        value.push_back(num);
        m[num] = value.size() - 1;
    }

    void remove(int num) {
        unordered_map<int, int>::iterator pos = m.find(num);
        if (pos == m.end()) {//unexist in the array
            return;
        }
        int index = pos->second;
        if (index != value.size() - 1) {
            int lastValue = value[value.size() - 1];
            swap(value[index], value[value.size() - 1]);//swap with the last value
            m[lastValue] = index;//update the index of the last value in the array
        }
        value.pop_back();//erase the last value in the array
        m.erase(num);//erase the num in the hashmap
    }

    int randomRemove() {
        int randIndex = rand() % value.size();
        int randValue = value[randIndex];
        if (randIndex != value.size() - 1) {
            int lastValue = value[value.size() - 1];
            swap(value[randIndex], value[value.size() - 1]);
            m[lastValue] = randIndex;
        }
        value.pop_back();
        m.erase(randValue);

        return randValue;
    }

    void print() {
        int size = value.size();
        for (int i = 0; i < size; i++) {
            cout<<value[i]<<" ";
        }
        cout<<endl;
    }

private:
    unordered_map<int, int> m;//number value to its index in the array
    vector<int> value;
};

int main() {
    ConstAccess ca;
    for (int i = 1; i < 10; i++) {
        ca.add(i);
    }
    int randomValue = ca.randomRemove();
    ca.remove(1);
    ca.print();

    return 1;
}
