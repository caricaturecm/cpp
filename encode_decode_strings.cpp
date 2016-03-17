//271. Encode and Decode Strings
//This alg is come from "count and say", it is right, but not very efficient
#include <iostream>
#include <vector>
using namespace std;

class Codec {
    public:

        string encode(vector<string>& strs) {
            string ret = "";
            for (auto str : strs) {
                ret += countStr(str);
                ret.push_back('#');
            }
            return ret;
        }

        vector<string> decode(string s) {
            vector<string> ret;
            int len = s.length(), count;
            string curStr = "";

            int i = 0;
            while (i < len) {
                if (isdigit(s[i])) {
                    count = s[i] - '0';
                    while (count) {
                        curStr.push_back(s[i + 1]);
                        count--;
                    }
                    i += 2;
                } else {
                    if (s[i] == 'e') {
                        i += 2;
                    } else {
                        ret.push_back(curStr);
                        curStr = "";
                        i++;
                    }
                }
            }

            return ret;
        }
    private:
        string countStr(string& str) {
            if (str.empty()) {
                return "ee";
            }
            int len = str.length();
            string ret = "";
            char preVal = str[0];
            int count = 1;

            for (int i = 1; i < len; i++) {
                if (str[i] == preVal) {
                    count++;
                } else {
                    ret += to_string(count) + preVal;
                    preVal = str[i];
                    count = 1;
                }
            }
            ret += (to_string(count) + preVal);

            return ret;
        }
};

int main() {
    vector<string> strs;
    strs.push_back("0");

    Codec s;
    string str = s.encode(strs);
    cout<<"encode str:"<<str<<endl;

    vector<string> newStrs = s.decode(str);

    for (auto t : newStrs) {
        cout<<t<<endl;
    }
    return 0;
}

// Your Codec object will be instantiated and called as such:
// // Codec codec;
// // codec.decode(codec.encode(strs));
