/*
 *Extract the line explain and block explain of one java/c++/c code file
 * */
#include <iostream>
#include <fstream>
using namespace std;

void extractExplain() {
    ifstream inFile("islands2.cpp");
    
    string line;
    while (getline(inFile, line)) {
        int index = line.find("//");
        if (index != string::npos) {
            cout<<line.substr(index)<<endl;
        }
        int index1 = line.find("/*");
        if (index1 != string::npos) {
            cout<<line.substr(index1)<<endl;
            int index2;
            while (getline(inFile, line)) {
                index2 = line.find("*/");
                if (index2 != string::npos) {
                    cout<<line.substr(0, index2 + 2)<<endl;
                    break;
                }
                cout<<line<<endl;
            }
        }
    }
}

int main() {
    extractExplain();
    return 1;
}
