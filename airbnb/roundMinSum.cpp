#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

struct mycmp {
    bool operator()(double num1, double num2) {
        int inum1 = (int)(num1);
        int inum2 = (int)(num2);
        return (num1 - inum1) < (num2 - inum2);
    }
};

vector<int> getIntegerList(vector<double>& nums, double roundVal) {
    int intSum = 0;
    int curNum;
    for (double num : nums) {
        curNum = (int)(num);
        intSum += curNum;
    }
    int ceilCount = roundVal - intSum;
    cout<<"ceilCount:"<<ceilCount<<endl;
    priority_queue<double, vector<double>, mycmp> pq;
    for (double num : nums) {
        pq.push(num);
    }

    vector<int> ret;
    while (!pq.empty()) {
        double dNum = pq.top();
        pq.pop();
        if (ceilCount > 0) {
            ret.push_back((int)(dNum) + 1);
            ceilCount--;
        } else {
            ret.push_back((int)(dNum));
        }
    }
    return ret;
}

int main() {
    double dnums[] = {1.2, 2.3, 3.4, 2.8};
    vector<double> vnums(dnums, dnums + 4);
    double sum = 0.0;
    for (double num : vnums) {
        sum += num;
    }
    double rval = round(sum);
    vector<int> intVals = getIntegerList(vnums, rval);

    for (int num : intVals) {
        cout<<num<<" ";
    }
    cout<<endl;
}
