#include <iostream>
#include <vector>
using namespace std;


/*
 *Empty: in == out
 *Full: out = in + 1, there is still one slot available, but we assume it is full already
 * */
class Circular {
public:
    Circular(int n) {
        buffer.assign(n, 0);
        in = 0;
        out = 0;
    }

    void addVal(int val) {
        if (out == (in + 1) % buffer.size()) {
            cout<<"full already."<<endl;
        } else {
            buffer[in] = val;
            in++;
        }
        in %= buffer.size();
    }

    int getVal() {
        int ret;
        if (in == out) {
            cout<<"buffer empty."<<endl;
            throw runtime_error("error");
        } else {
            ret = buffer[out];
            out++;
        }
        out %= buffer.size();
        return ret;
    }

private:
    vector<int> buffer;
    int in, out;
};

int main() {
    Circular circularBuffer(3);
    circularBuffer.addVal(1);
    circularBuffer.addVal(2);
    circularBuffer.addVal(3);

    int val = circularBuffer.getVal();
    cout<<val<<endl;
    val = circularBuffer.getVal();
    cout<<val<<endl;
    val = circularBuffer.getVal();
    cout<<val<<endl;
    return 0;
}
