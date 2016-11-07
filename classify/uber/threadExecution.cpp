//
// Created by ChenMin on 10/11/16.
//

/*
 * 给你一个thread的log，每条log有如下信息: (thread_id, start_time, execution_time)，
 * 然后写个程序统计总共需要多少时间完成所有的进程。假设优先级都一样，而且是抢占式。
 *
 * 只是求thread完成的总时间，记录当前到的时间，和下一个开始的thread的开始时间
 *
 * http://www.1point3acres.com/bbs/thread-193176-1-1.html
 * */
#include <iostream>
#include <vector>
using namespace std;

struct Thread {
    int id, startTime, executionTime;
    Thread(int iid, int sTime, int eTime) : id(iid), startTime(sTime), executionTime(eTime) {}
};

class Solution {
public:
    int threadTime(vector<Thread>& threads) {
        if (threads.empty()) {
            return 0;
        }
        sort(threads.begin(), threads.end(), mycmp);
        int curTime = threads[0].startTime, ret = 0;

        for (auto thread : threads) {
            if (thread.startTime > curTime) {//wait first
                curTime += (thread.startTime - curTime);
                ret += (thread.startTime - curTime);
            }
            //execution
            curTime += thread.executionTime;
            ret += thread.executionTime;
        }
        return ret;
    }

private:
    bool static mycmp(Thread& a, Thread& b) {
        return a.startTime < b.startTime;
    }
};

int main() {
    vector<Thread> threads;
    threads.push_back(Thread(0, 20, 10));
    threads.push_back(Thread(1, 25, 15));
    threads.push_back(Thread(2, 0, 10));
    threads.push_back(Thread(3, 25, 5));

    Solution sol;
    int ret = sol.threadTime(threads);
    cout<<"consume time:"<<ret<<endl;
}