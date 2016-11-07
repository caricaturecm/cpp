//
// Created by ChenMin on 10/9/16.
//
// find all duplicate files in current directory and sub directory
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;


class DuplicateFile {
public:
    vector<vector<string>> findDuplicateFiles(const char *path) {
        //dfs get all files
        getAllFiles(path);

        unordered_map<long, vector<string>> size2Files;
        string curFile;

        while (!files.empty()) {
            curFile = files.top();
            files.pop();
            long size = getSize(curFile);

            size2Files[size].push_back(curFile);
        }

        char* block;
        streampos pos = 0;
        unordered_map<string, vector<string>> hash2Files;
        for (auto files : size2Files) {
            if (files.second.size() > 1) {
                vector<string> curFiles = files.second;
                for (auto file : curFiles) {
                   ifstream myfile(file, ios::in);
                    if (myfile.is_open()) {
                        block = new char[1000];
                        myfile.seekg(pos, ios::beg);
                        myfile.read(block, 1000);

                        string hashValue = getHashValue(block);
                        hash2Files[hashValue].push_back(file);
                    }
                }
            }
        }
        pos += 1000;

        vector<vector<string>> ret;
        while (!hash2Files.empty()) {
            unordered_map<string, vector<string>> tmp;
            for (auto files : hash2Files) {
                if (files.second.size() > 1) {
                    vector<string> curFiles;
                    for (auto file : curFiles) {
                        ifstream myfile(file, ios::in);
                        myfile.seekg(0, ios::end);
                        streampos end = myfile.tellg();
                        if (pos >= end) {
                            ret.push_back(files.second);
                        } else {
                            if (myfile.is_open()) {
                                block = new char[1000];
                                myfile.seekg(pos, ios::beg);
                                myfile.read(block, 1000);

                                string hashValue = getHashValue(block);
                                tmp[hashValue].push_back(file);
                            }
                        }
                    }
                }
            }
            hash2Files = tmp;
            pos += 1000;
        }

        return ret;
    }

private:

    string getHashValue(char* block) {
        return "test";
    }

    long getSize(string filePath) {
        streampos begin, end;
        ifstream myfile(filePath, ios::binary);
        begin = myfile.tellg();
        myfile.seekg(0, ios::end);
        end = myfile.tellg();
        myfile.close();
        long size = end - begin;
        return size;
    }

    void getAllFiles(const char* dirPath) {
        DIR* dp;
        dirent *d;

        dp = opendir(dirPath);
        while ((d = readdir(dp)) != NULL) {
            if (d->d_type == DT_REG) {
                files.push(string(dirPath) + "/" + string(d->d_name));
            } else if (d->d_type == DT_DIR && string(d->d_name) != "." && string(d->d_name) != "..") {
                string curPath = string(dirPath) + "/" + string(d->d_name);
                getAllFiles(curPath.c_str());
            }
        }
        closedir(dp);
    }

    stack<string> files;//filename to filepath
    unordered_map<long, unordered_map<string, string>> hashFiles;
};

int main() {
    DuplicateFile df;
    const char* path = "/Users/caricaturecm/cpp/leetcode";
    vector<vector<string>> ret = df.findDuplicateFiles(path);

    cout<<"ret size:"<<ret.size()<<endl;

    for (auto files : ret) {
        for (auto file : files) {
            cout<<file<<" ";
        }
        cout<<endl;
    }
    return 0;
}
