/*#include <iostream>
#include <vector>
using namespace std;


vector<string> csvParser(string& csvLine) {
    vector<string> ret;
    string curField = "";
    int len = csvLine.length();
    bool inQuote = false;

    for (int i = 0; i < len; i++) {
        if (inQuote) {
            if (csvLine[i] == '"') {
                if (i == len - 1) {
                    ret.push_back(curField);
                    curField = "";
                } else if (csvLine[i + 1] == '"') {
                    curField.push_back('"');
                    i++;
                } else {
                    inQuote = false;
                }
            } else {
                curField.push_back(csvLine[i]);
            }
        } else {
            if (csvLine[i] == '"') {
                inQuote = true;
            } else if (csvLine[i] == ',') {
                ret.push_back(curField);
                curField = "";
            } else {
                curField.push_back(csvLine[i]);
            }
        }
    }
    if (!curField.empty()) {
        ret.push_back(curField);
    }
    return ret;
}

string encodeFields(vector<string>& fields) {
    string ret = "";
    int size = fields.size();

    for (int i = 0; i < size; i++) {
        ret += fields[i];
        ret.push_back('|');
    }
    ret.pop_back();
    return ret;
}
int main() {
    string str1 = "a,b,c,d";
    vector<string> fields = csvParser(str1);
    string parserStr = encodeFields(fields);
    cout<<"after parser:"<<parserStr<<endl;

    string str2 = "\"ab\"\"\"\"c,d\"\"\"\"ef\",number,name,\"\"\"address\"\"\"";
    fields = csvParser(str2);
    parserStr = encodeFields(fields);
    cout<<"parser str2:"<<parserStr<<endl;

    return 0;
}*/

#include <iostream>
#include <vector>
using namespace std;

class CsvParser {
public:
    string parser(string& str) {
        if (str.empty()) {
            return "";
        }

        int len = str.length();
        vector<string> segs;
        string curSeg = "";
        bool inQuote = false;

        for (int i = 0; i < len; i++) {
            if (inQuote) {
                if (str[i] == '"') {
                    if (i == len - 1) {
                        segs.push_back(curSeg);
                        curSeg = "";
                    } else if (str[i + 1] == '"') {
                        curSeg.push_back('"');
                        i++;
                    } else {
                        inQuote = false;
                    }
                } else {
                    curSeg.push_back(str[i]);
                }
            } else {
                if (str[i] == '"') {
                    inQuote = true;
                } else if (str[i] == ',') {
                    segs.push_back(curSeg);
                    curSeg = "";
                } else {
                    curSeg.push_back(str[i]);
                }
            }
        }

        if (!curSeg.empty()) {
            segs.push_back(curSeg);
        }

        string ret = unionStrs(segs);
        return ret;
    }

private:
    string unionStrs(vector<string>& strs) {
        string ret = "";
        if (strs.empty()) {
            return ret;
        }

        int size = strs.size();
        ret = strs[0];
        for (int i = 1; i < size; i++) {
            ret.push_back('|');
            ret += strs[i];
        }
        return ret;
    }
};

int main() {
    string str1 = "a,b,c,d";
    CsvParser sol;
    string ret = sol.parser(str1);
    cout<<"after parser:"<<ret<<endl;

    string str2 = "\"ab\"\"\"\"c,d\"\"\"\"ef\",number,name,\"\"\"address\"\"\"";
    ret = sol.parser(str2);
    cout<<"parser str2:"<<ret<<endl;

    return 0;
}