//
// Created by ChenMin on 10/31/16.
//
/*
 * 每次给你一个(x, y, iter)，问你在iter这张图中在(x, y)坐标的点是第几个？.
解法：从大往小左，逐渐细化。每次先算出当前点在当前iter是在第几象限，先加上前面那些跳过去的象限里的点。
 然后找到这个点在这个象限的相对坐标新(x,y)，但是还不够！对于三四象限的点，因为方向变了，需要做镜面映射，
 把(x,y)映射成(y,x) (第三象限) 或 (M-y, M-x) (第四象限)，M是象限的长宽。
 *
 * */
#include <iostream>
#include <cmath>
using namespace std;

int hilbert_curve(int x, int y, int iter) {
    if (iter == 0) {
        return 1;
    }
    int halfLen = pow(2, iter - 1);
    int quadNum = pow(2, 2 * iter - 2);

    if (x >= halfLen && y >= halfLen) {
        return 2 * quadNum + hilbert_curve(x - halfLen, y - halfLen, iter - 1);
    } else if (x < halfLen && y >= halfLen) {
        return quadNum + hilbert_curve(x, y - halfLen, iter - 1);
    } else if (x < halfLen && y < halfLen) {
        return hilbert_curve(y, x, iter - 1);
    } else {
        return 3 * quadNum + hilbert_curve(halfLen - 1 - y, 2 * halfLen - 1 - x, iter - 1);
    }
}

int main() {
    int ret = hilbert_curve(0, 0, 1);
    cout<<"ret:"<<ret<<endl;
    return 0;
}