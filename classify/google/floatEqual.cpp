//
// Created by ChenMin on 10/2/16.
//

/*
 * folat, double equality
 * */
#include <iostream>
#include <math.h>
using namespace std;

bool equal(double a, double b) {
    return fabs(a - b) < 0.000001;
//    return fabs(a - b) < EPSILON;
}

int main() {
    double num1 = 1.2, num2 = 1.2000101;
    if (equal(num1, num2)) {
        cout<<"equal"<<endl;
    } else {
        cout<<"not equal"<<endl;
    }
}

