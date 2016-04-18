/*
 * One coin, throw n times store the results in an array, H/T represents the two sides
 * if you can only flip one result, get the length of the longest consecutive subarray
 * */
#include <iostream>
#include <vector>
using namespace std;

int longestSubarrayOneFlip(vector<char>& sides) {
    int maxL = INT_MIN, size = sides.size(), countH = 0, countT = 0;

    int l = 0;
    for (int r = 0; r < size; r++) {
        sides[r] == 'H' ? countH++ : countT++;

        if (countH > 1 && countT > 1) {
            maxL = max(maxL, r - l);
            while (countH > 1 && countT > 1) {
                sides[l] == 'H' ? countH-- : countT--;
                l++;
            }
        }
    }

    return maxL;
}

int main() {
    char a[] = {'H', 'T', 'T', 'H', 'H', 'H', 'T'};
    vector<char> sides(a, a + 7);
    int ret = longestSubarrayOneFlip(sides);
    cout<<"longest subarray with one flip:"<<ret<<endl;
}
