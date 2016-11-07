//
// Created by ChenMin on 10/29/16.
//
/*
 *http://www.1point3acres.com/bbs/thread-147112-1-1.html
 *
 *
 *  CIDR表达是： ip地址/掩码位数 表示一个区间
    比如 0.0.0.8 / 30 就是以0.0.0.8为准，前30位不能变--》0.0.0.(0000 10 00)--0.0.0.(0000 10 11)
    然后给你一个起始ip，和数量。用最少的cidr表示这个区间
 * */
/*#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class CIDR {
public:
    CIDR() {
        unsigned int nums[] = {0x00000000,
                      0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
                      0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
                      0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
                      0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
                      0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
                      0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
                      0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
                      0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff
        };
        cidrMask.assign(nums, nums + sizeof(nums) / sizeof(unsigned int));
    }

    vector<string> minCidr(string startIp, int count) {
        unsigned int start = ip2Long(startIp);
        unsigned int end = start + count - 1;

        vector<string> ret;
        while (start <= end) {
            int oneCount = 32;
            while (oneCount > 0) {
                unsigned int mask = cidrMask[oneCount - 1];
                unsigned int masked = start & mask;
                if (masked != start) {
                    break;
                }
                oneCount--;
            }

            int zeroCount = 32 - oneCount;

            double lowerZero = log(end - start + 1) / log(2);
            int needZero = floor(lowerZero);
            if (zeroCount > needZero) {
                zeroCount = needZero;
            }
            string ip = long2Ip(start);
            ret.push_back(ip + "/" + to_string(32 - zeroCount));
            start += pow(2, zeroCount);
        }
        return ret;
    }
private:
    string long2Ip(unsigned int ipNum) {
        string ret = "";
        ret += to_string(ipNum >> 24);
        ret.push_back('.');
        ret += to_string((ipNum & 0x00FFFFFF) >> 16);
        ret.push_back('.');
        ret += to_string((ipNum & 0x0000FFFF) >> 8);
        ret.push_back('.');
        ret += to_string((ipNum & 0x000000FF));

        return ret;
    }

    unsigned int ip2Long(string ip) {
        vector<unsigned int> nums;
        ip.push_back('.');
        int oldPos = 0, pos;
        pos = ip.find_first_of('.');

        while (pos != string::npos) {
            nums.push_back(stoi(ip.substr(oldPos, pos - oldPos)));
            oldPos = pos + 1;
            pos = ip.find_first_of('.', oldPos);
        }

        return (nums[0] << 24) + (nums[1] << 16) + (nums[2] << 8)+ nums[3];
    }

    vector<unsigned int> cidrMask;
};


int main() {
    string startIp = "1.1.1.111";
    int count = 10;
    CIDR cidr;
    vector<string> ret = cidr.minCidr(startIp, count);

    for (auto str : ret) {
        cout<<str<<endl;
    }
    return 0;
}*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class CIDR {
public:
    CIDR() {
        unsigned int nums[] = {
                0x00000000,
                0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
                0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
                0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
                0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
                0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
                0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
                0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
                0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff
        };
        cidrMask.assign(nums, nums + sizeof(nums) / sizeof(unsigned int));
    }

    vector<string> minCidr(string& startIp, int count) {
        unsigned int start = ip2int(startIp);
        unsigned int end = start + count - 1;

        vector<string> ret;
        while (start <= end) {
            int oneCount = 32;
            while (oneCount > 0) {
                unsigned int mask = cidrMask[oneCount - 1];
                unsigned int masked = start & mask;

                if (masked != start) {
                    break;
                }
                oneCount--;
            }

            int zeroCount = 32 - oneCount;
            int needZero = (int)(log(end - start + 1 ) / log(2));
            if (zeroCount > needZero) {
                zeroCount = needZero;
            }
            string strIp = int2Ip(start);
            ret.push_back(strIp + "/" + to_string(32 - zeroCount));
            start += pow(2, zeroCount);
        }
        return ret;
    }

private:
    string int2Ip(int num) {
        string ret = "";
        ret += to_string(num >> 24);
        ret.push_back('.');
        ret += to_string((num & 0x00FFFFFF) >> 16);
        ret.push_back('.');
        ret += to_string((num & 0x0000FFFF) >> 8);
        ret.push_back('.');
        ret += to_string(num & 0x000000FF);
        return ret;
    }

    unsigned int ip2int(string& strIp) {
        vector<unsigned int> nums;
        int oldPos = 0, pos;
        strIp.push_back('.');

        pos = strIp.find_first_of('.');
        while (pos != string::npos) {
            nums.push_back(stoi(strIp.substr(oldPos, pos - oldPos)));
            oldPos = pos + 1;
            pos = strIp.find_first_of('.', oldPos);
        }
        return (nums[0] << 24) + (nums[1] << 16) + (nums[2] << 8) + nums[3];
    }


    vector<unsigned int> cidrMask;
};


int main() {
    string startIp = "1.1.1.111";
    int count = 10;
    CIDR cidr;
    vector<string> ret = cidr.minCidr(startIp, count);

    for (auto str : ret) {
        cout<<str<<endl;
    }
    return 0;
}