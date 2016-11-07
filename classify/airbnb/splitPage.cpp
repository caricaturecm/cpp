/*#include <iostream>
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
        if (page1.id == page2.id) {//no duplicate key
            return false;
        }
        return page1.name < page2.name;//sort
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
//    vector<string> posts;
//    string post1 = "astreet, 1, this is a good hourse";
//    string post2 = "aheadhi, 2, come one";
//    string post3 = "bstreet, 1, three test";
//    string post4 = "cstreet, 1, one test";
//    string post5 = "dstreet, 4, four test";
//    string post6 = "estreet, 1, one test again";
//    string post7 = "fstreet, 3, test 3 again";
//
//    posts.push_back(post1);
//    posts.push_back(post2);
//    posts.push_back(post3);
//    posts.push_back(post4);
//    posts.push_back(post5);
//    posts.push_back(post6);
//    posts.push_back(post7);

    vector<string> posts = {
            "300.1,1,SanFrancisco",
            "209.1,4,SanFrancisco",
            "208.1,20,SanFrancisco",
            "207.1,23,SanFrancisco",
            "300.1,1,Oakland",
            "205.1,1,SanFrancisco",

            "103.1,1,Oakland",
            "206.2,16,Oakland",
            "5.1,1,Oakland",
    };


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
}*/

/*
 * set, key_comp, cannot use both compare and remove duplicate
 *
 * something as following is not correct
 *
 *   struct mycmp {
        bool operator()(const PageItem& a, const PageItem& b) {
            if (a.id == b.id) {
                return false;
            }
            return a.score > b.score;
        }
    };


    set is a red-black tree, the item with the same id maybe in another subtree, it will not be found
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

class PageList {
public:
    vector<vector<string>> getPages(vector<string>& inputPages, int k) {
        vector<vector<string>> ret;
        if (inputPages.empty()) {
            return ret;
        }

        int size = inputPages.size();
        vector<unordered_set<string>> pageIds;
        vector<set<PageItem, mycmp>> pages;

        for (int i = 0; i < size; i++) {
            PageItem page = getPageItem(inputPages[i]);

            bool isInsert = false;
            for (int j = 0; j < pages.size(); j++) {
                if (pageIds[j].find(page.id) == pageIds[j].end() && pageIds[j].size() < k) {
                    isInsert = true;
                    pageIds[j].insert(page.id);
                    pages[j].insert(page);
                    break;
                }
            }
            if (!isInsert) {
                unordered_set<string> newPageIds;
                set<PageItem, mycmp> newPage;

                newPageIds.insert(page.id);
                newPage.insert(page);

                pageIds.push_back(newPageIds);
                pages.push_back(newPage);
            }
        }

        size = pages.size();
        for (int i = 0; i < size; i++) {
            vector<string> msgPage;
            set<PageItem, mycmp> onePage = pages[i];
            for (auto it = onePage.begin(); it != onePage.end(); it++) {
                msgPage.push_back(it->msg);
            }
            ret.push_back(msgPage);
        }
        return ret;
    }

private:
    struct PageItem {
        string id, msg;
        double score;

        PageItem(string iid, double sscore, string mmsg) : id(iid), score(sscore), msg(mmsg) {}
    };

    struct mycmp {
        bool operator()(const PageItem& a, const PageItem& b) {
            return a.score > b.score;
        }
    };

    PageItem getPageItem(string& str) {
        int pos = str.find_first_of(',');
        string id = str.substr(0, pos);

        int oldPos = pos + 1;
        pos = str.find_first_of(',', oldPos);
        oldPos = pos + 1;
        pos = str.find_first_of(',', oldPos);
        double score = stold(str.substr(oldPos, pos - oldPos));

        PageItem pageItem(id, score, str);
        return pageItem;
    }
};


int main() {
    vector<string> pages = {
            "1,28,300.1,SanFrancisco",
            "4,5,209.1,SanFrancisco",
            "20,7,208.1,SanFrancisco",
            "23,8,207.1,SanFrancisco",
            "16,10,206.1,Oakland",
            "1,16,205.1,SanFrancisco",
            "6,29,204.1,SanFrancisco",
            "7,20,203.1,SanFrancisco",
            "8,21,202.1,SanFrancisco",
            "2,18,201.1,SanFrancisco",
            "2,30,200.1,SanFrancisco",
            "15,27,109.1,Oakland",
            "10,13,108.1,Oakland",
            "11,26,107.1,Oakland",
            "12,9,106.1,Oakland",
            "13,1,105.1,Oakland",
            "22,17,104.1,Oakland",
            "1,2,103.1,Oakland",
            "28,24,102.1,Oakland",
            "18,14,11.1,SanJose",
            "6,25,10.1,Oakland",
            "19,15,9.1,SanJose",
            "3,19,8.1,SanJose",
            "3,11,7.1,Oakland",
            "27,12,6.1,Oakland",
            "1,3,5.1,Oakland",
            "25,4,4.1,SanJose",
            "5,6,3.1,SanJose",
            "29,22,2.1,SanJose",
            "30,23,1.1,SanJose"
    };

    PageList sol;
    vector<vector<string>> ret = sol.getPages(pages, 12);

    for (auto page : ret) {
        cout<<"One Page"<<endl;
        for (auto item : page) {
            cout<<item<<endl;
        }
    }

    return 0;
}