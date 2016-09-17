#include <iostream>
#include <vector>
#include <set>
using namespace std;

class PageItem {
public:
    string name, id, msg;
    PageItem(string n, string i, string m) {
        name = n;
        id = i;
        msg = m;
    }
};

struct Mycmp {
    bool operator()(const PageItem& page1, const PageItem& page2) {
        if (page1.id == page2.id) {
            return false;
        }
        return page1.name < page2.name;
    }
};

vector<vector<string> > getPages(vector<string>& posts) {
    vector<set<PageItem, Mycmp> > pageList;
    for (string post : posts) {
        int pos = post.find_first_of(',');
        string name = post.substr(0, pos);
        int oldPos = pos + 1;
        pos = post.find_first_of(',', oldPos);
        string id = post.substr(oldPos, pos - oldPos);
        PageItem pageItem(name, id, post);

        bool insertExistPage = false;
        for (int i = 0; i < pageList.size(); i++) {
            if (pageList[i].find(pageItem) == pageList[i].end() && pageList[i].size() < 3) {
                pageList[i].insert(pageItem);
                insertExistPage = true;
                break;
            }
        }
        if (insertExistPage == false) {
            set<PageItem, Mycmp> newPage;
            newPage.insert(pageItem);
            pageList.push_back(newPage);
        }
    }

    vector<vector<string> > ret;
    int pageSize = pageList.size();
    for (int i = 0; i < pageSize; i++) {
        vector<string> curPage;
        for (set<PageItem, Mycmp>::iterator it = pageList[i].begin(); it != pageList[i].end(); it++) {
            curPage.push_back(it->msg);
        }
        ret.push_back(curPage);
    }
    return ret;
}

int main() {
    vector<string> posts;
    string post1 = "astreet, 1, this is a good hourse";
    string post2 = "aheadhi, 2, come one";
    string post3 = "bstreet, 3, three test";
    string post4 = "cstreet, 1, one test";
    string post5 = "dstreet, 4, four test";
    string post6 = "estreet, 1, one test again";
    string post7 = "fstreet, 3, test 3 again";

    posts.push_back(post1);
    posts.push_back(post2);
    posts.push_back(post3);
    posts.push_back(post4);
    posts.push_back(post5);
    posts.push_back(post6);
    posts.push_back(post7);

    vector<vector<string> > pages =  getPages(posts);
    int pageSize = pages.size();
    
    for (int i = 0; i < pageSize; i++) {
        vector<string> curPage = pages[i];
        for (int j = 0; j < curPage.size(); j++) {
            cout<<curPage[j]<<endl;
        }
        cout<<endl;
    }
    return 0;
}
