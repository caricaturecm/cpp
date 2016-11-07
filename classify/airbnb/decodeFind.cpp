#include <iostream>
#include <vector>
using namespace std;

string decode(string& str) {
    if (str == "HiJ") {
        return "123";
    }
    return "";
}

string backTrack(string& badStr, int index) {
    if (index == badStr.length()) {
        return decode(badStr);
    }
   
    string dstr = decode(badStr);
    if (dstr.length()) {
        return dstr;
    }

    badStr[index] = tolower(badStr[index]);
    dstr = backTrack(badStr, index + 1);
    if (dstr.length()) {
        return dstr;
    }

    badStr[index] = toupper(badStr[index]);
    dstr = backTrack(badStr, index + 1);
    if (dstr.length()) {
        return dstr;
    }
    
    return "";
}

string decodeFind(string& badStr) {
    int len = badStr.length();
    return backTrack(badStr, 0);
}

int main() {
    string badStr = "hij";
    string decodeInt = decodeFind(badStr);
    cout<<decodeInt<<endl;
    return 0;
}


/*void backTrack(string& str, int index, string& cur, vector<string>& ret) {
    if (index == str.length()) {
        ret.push_back(cur);
        return;        
    }

    cur.push_back(tolower(str[index]));
    backTrack(str, index + 1, cur, ret);
    cur.pop_back();

    cur.push_back(toupper(str[index]));
    backTrack(str, index + 1, cur, ret);
    cur.pop_back();
}

vector<string> getAllStrs(string& str) {
    vector<string> ret;
    string cur = "";
    backTrack(str, 0, cur, ret);
    return ret;
}

int main() {
    string str = "hij";
    vector<string> strs = getAllStrs(str);
    for (int i = 0; i < strs.size(); i++) {
        cout<<strs[i]<<endl;
    }
    return 0;
}*/
