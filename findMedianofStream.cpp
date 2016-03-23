//295. Find Median from Data Stream
/*
 * Why I always feel this is so clever alg
 *
 * use to priority queue, one store the numbers, the ohter store the negative of the input number,
 * so can maintain both the top data is the middle one of the data stream
 *
 * default priority queue in c++ is max heap
 *
 * */

class MedianFinder {
    public:

        void addNum(int num) {
            smallHalf.push(num);
            int maxNum = smallHalf.top();
            smallHalf.pop();
            largeHalf.push(-maxNum);
            if (smallHalf.size() < largeHalf.size()) {
                smallHalf.push(-largeHalf.top());
                largeHalf.pop();
            }
        }

        double findMedian() {
            if (smallHalf.size() > largeHalf.size()) {
                return smallHalf.top();
            } else {
                return (smallHalf.top() - largeHalf.top()) / 2.0; 
            }
        }

    private:
        priority_queue<int> smallHalf, largeHalf;
};


