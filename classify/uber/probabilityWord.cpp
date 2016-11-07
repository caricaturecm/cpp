//
// Created by ChenMin on 10/11/16.
//

/*
 * http://www.1point3acres.com/bbs/thread-189229-1-1.html
 *
 * assuming a list of words appear with a given probability:
 * example (hello, 0.2), (world, 0.3), (ok, 0.5).
 * now generate a word according to the probability
 * */
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    Solution(unordered_map<string, float>& wordsWithPro) {
        for (auto it = wordsWithPro.begin(); it != wordsWithPro.end(); it++) {
            words.push_back(it->first);
            if (probabilities.empty()) {
                probabilities.push_back(it->second);
            } else {
                probabilities.push_back(probabilities.back() + it->second);
            }
        }
        int size = wordsWithPro.size();
        for (int i = 0; i < size; i++) {
            cout<<words[i]<<","<<probabilities[i]<<endl;
        }
    }

    string getRandomWord() {
        int rnum = rand();
        float rdPro = (float)(rnum) / (float)(RAND_MAX);
        int index = lowerBound(probabilities, rdPro);
        return words[index];
    }

private:
    int lowerBound(vector<float>& nums, float target) {
        int low = 0, high = nums.size() - 1, mid, ret;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (nums[mid] > target || fabs(nums[mid] - target) < 0.000001) {
                ret = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ret;
    }

    vector<string> words;
    vector<float> probabilities;
};


int main() {
    unordered_map<string, float> words;
    words.insert(make_pair("hello", 0.5));
    words.insert(make_pair("world", 0.498));
    words.insert(make_pair("min", 0.002));
    Solution sol(words);

    string word = sol.getRandomWord();
    cout<<"word:"<<word<<endl;
    return 0;
}
