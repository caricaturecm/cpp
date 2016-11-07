//
// Created by ChenMin on 10/29/16.
//

/*
 *
 * 一个餐馆，菜单上各种食物价格如下
A， $ X.XX
B， $ Y.YY
C， $ Z.ZZ
D,  $ ...


问现在一个人有 一定数额的钱，比如 $MM.MM，如何点菜才能把钱全部花完？
面试官要求列出所有可能的组合
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class OrderDish {
public:
    vector<vector<string>> orderDish(vector<pair<string, double>>& dish, double money) {
        vector<pair<string, long>> ldish;
        for (auto item : dish) {
            ldish.push_back(make_pair(item.first, (long)(item.second * 100)));
        }
        long lmoney = (long)(money * 100);

        sort(ldish.begin(), ldish.end(), mycmp);

        vector<vector<string>> ret;
        vector<string> cur;
        backTrack(ldish, 0, cur, ret, lmoney);
        return ret;
    }

    void backTrack(vector<pair<string, long>>& dish, int index, vector<string>& cur, vector<vector<string>>& ret, long money) {
        if (money == 0) {
            ret.push_back(cur);
            return;
        }
        for (int i = index; i <dish.size(); i++) {
            if (dish[i].second > money) return;
            cur.push_back(dish[i].first);
            backTrack(dish, i + 1, cur, ret, money - dish[i].second);
            cur.pop_back();
        }
    }

private:
    bool static mycmp(pair<string, long>& lhs, pair<string, long>& rhs) {
        return lhs.second < rhs.second;
    }
};

int main() {
    vector<pair<string, double>> dish;
    dish.push_back(make_pair("A", 1.55));
    dish.push_back(make_pair("B", 3.61));
    dish.push_back(make_pair("C", 1.55));
    dish.push_back(make_pair("D", 4.32));
    dish.push_back(make_pair("E", 1.55));

    OrderDish sol;
    vector<vector<string>> ret = sol.orderDish(dish, 6.71);
    cout<<"return val:"<<endl;
    for (auto cur : ret) {
        for (auto item : cur) {
            cout<<item<<" ";
        }
        cout<<endl;
    }
    return 0;
}