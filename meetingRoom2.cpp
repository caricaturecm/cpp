#include <iostream>
//#include <set>
#include <vector>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

/*
 * It is really clever to come out this alg
 * sort the start time and end time of all meetings
 * begin with the first end time,
 * scan the begin time, if the current begin time smaller than current end time, then count++, no meeting room can be
 * released
 * if the begin time > current end time, then the meeting can be released for current begin meeting,
 * */
class Solution {
    public:
        int minMeetingRooms(vector<Interval>& intervals) {
           // set<int> starts, ends;//cannot use set here, although set is sorted, elements should be unique
            vector<int> starts, ends;
            for (auto interval : intervals) {
                starts.push_back(interval.start);
                ends.push_back(interval.end);
            }
            sort(starts.begin(), starts.end());
            sort(ends.begin(), ends.end());

            int count = 0, size = intervals.size(), endIndex = 0;
            for (int i = 0; i < size; i++) {
                if (starts[i] < ends[endIndex]) {
                    count++;
                } else {
                    endIndex++;
                }
            }

            return count;
        }
};

int main() {
    Solution s;
    Interval interval(2, 7);
    vector<Interval> intervals;
    intervals.push_back(interval);

    int num = s.minMeetingRooms(intervals);
    cout<<num<<endl;
    return 0;
}
