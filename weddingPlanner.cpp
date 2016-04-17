#include <iostream>
#include <vector>
using namespace std;

class WeddingPlanner {
public:
    WeddingPlanner(vector<int> inums, vector<float> fnums) {
        intNums = inums;
        floatNums = fnums;
    }

    float getFloat(int num) {
        int index = findInt(num);
        if (index != -1) {
            return floatNums[index];
        }
        int left = findLow(num), right = left + 1;
        int intDiff = intNums[right] - intNums[left];
        float floatDiff = floatNums[right] - floatNums[left];
        return (num * floatDiff) / intDiff;
    }
private:
    int findLow(int num) {
        int size = intNums.size(), low = 0, high = size - 1, mid;
        while (low < high) {
            mid = low + (high - low) / 2;
            if (num < intNums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low == high ? low : low - 1;
    }

    int findInt(int num) {
        int size = intNums.size(), low = 0, high = size - 1, mid;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (num == intNums[mid]) {
                return mid;
            } else if (num > intNums[mid]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

    vector<int> intNums;
    vector<float> floatNums;
};


int main() {
    int a[] = {10, 20, 50, 100, 500};
    float b[] = {1.2, 2.5, 3.8, 6.9, 10.4};
    vector<int> inums(a, a + 5);
    vector<float> fnums(b, b + 5);

    WeddingPlanner planer(inums, fnums);
    cout<<planer.getFloat(10)<<endl;
    cout<<planer.getFloat(30)<<endl;

    return 0;
}
