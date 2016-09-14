#include <set>
#include <iostream>
using namespace std;

struct Triple {
    string name;
    string id;
    string str;

    Triple(string strName, string strId, string strStr) {
        name = strName;
        id = strId;
        str = strStr;
    }
    
    bool operator==(Triple& rhs) {
        return id == rhs.id;
    }
};

//whether two element keys are equivalent (by comparing them reflexively: they are equivalent if !comp(a,b) &&
//!comp(b,a))
struct mycmp {
    bool operator()(const Triple& lhs, const Triple& rhs) {
        if (lhs.id == rhs.id) return false; //Two elements of a set are considered equivalent if key_comp returns false reflexively 
        return lhs.name < rhs.name;
    }
};

int main() {
    set<Triple, mycmp> myset;
    Triple t1("min", "12", "test1");
    Triple t2("chen", "23", "test2");
    Triple t3("ye", "34", "test3");
    Triple t4("lin", "12", "test4");
//    Triple t5("lin", "123", "test5");

    myset.insert(t1);
    myset.insert(t2);
    myset.insert(t3);
    myset.insert(t4);
//    myset.insert(t5);

    for (set<Triple>::iterator it = myset.begin(); it != myset.end(); it++) {
        cout<<(*it).name<<endl;
    }
}
