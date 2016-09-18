#include <iostream>
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
}
