//
// Created by ChenMin on 10/1/16.
//
/*
 * read file line by line
 * */
#include <iostream>
#include <fstream>
using namespace std;

class ReadFile {
public:
    void readLine(string& filePath) {
        ifstream fs;
        fs.open(filePath);
        string line = "";
        while (!fs.eof()) {
            getline(fs, line);
            cout<<"current line:"<<line<<endl;
        }

        fs.close();
    }
};

int main() {
    string file = "/Users/caricaturecm/cpp/algorithm/google/test.txt";
    ReadFile rf;
    rf.readLine(file);
    return 0;
}
