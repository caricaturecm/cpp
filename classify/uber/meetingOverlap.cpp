//
// Created by ChenMin on 10/10/16.
//
/*
 * 有一大堆meeting， 有start time和end time，都是integer，且在一天之内，代表一天内的第几分钟。
 * 然后让返回boolean代表这些是否有overlap，然后楼主就naive了，
 * 就写了个comparator sort了，按start time 排序后一个个检查下一个的start time是否小于上一个的end time。
 * 然后小哥说有没有更好的办法，提示了一下说用一个数组。然后楼主恍然大悟，就开了个1440 大小的bit的数组写了个O(n)的。
 * */
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bool isOverlap(vector<pair<int, int>>& meetings) {
    bitset<1440> oneDay(0);
    for (auto meet : meetings) {
        for (int i = meet.first; i <= meet.second; i++) {
            if (oneDay[i] == 1) {
                return false;
            }
            oneDay[i] = 1;
        }
    }
    return true;
}

int main() {
    vector<pair<int, int>> meetings;
    meetings.push_back(make_pair(0, 10));
    meetings.push_back(make_pair(100, 208));
    meetings.push_back(make_pair(50, 60));
//    meetings.push_back(make_pair(30, 50));

    bool ret = isOverlap(meetings);
    cout<<"ret:"<<ret<<endl;
    return 0;
}
