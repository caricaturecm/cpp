//
// Created by ChenMin on 10/10/16.
//
/*
 * sqrt of a float number
 * */
#include <iostream>
#include <math.h>
using namespace std;

double floatSqt(float num) {
    if (num <= 0) {
        return 0.0;
    }
    double low = 0, high = ceil(num), mid;//here should be ceil(num), avoid the case num < 1
    mid = (low + high) / 2.0;
    cout<<"mid:"<<mid<<endl;

    while (fabs(num - mid * mid) > 0.000001) {
        if (mid * mid <= num) {
            low = mid;
        } else {
            high = mid;
        }
        mid = (high + low) / 2.0;
        cout<<"mid:"<<mid<<endl;
    }
    return mid;
}

int main() {
    float num = 100.9;
    double ret = floatSqt(num);
    cout<<"ret:"<<ret<<endl;
    return 0;
}

