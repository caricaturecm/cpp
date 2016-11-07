//
// Created by ChenMin on 10/12/16.
//

/*
 * http://www.1point3acres.com/bbs/thread-205498-1-1.html
 *
 * int memmove(void * src, void * dst, int size)
具体就是要把src的memory移到dst的memory里，转移size个byte。。
 * */
#include <iostream>
using namespace std;

void mymemcopy(void* dst, void* src, size_t size) {
    char* cdst = (char*) dst;//can not assign void* to char*
    char* csrc = (char*) src;

    for (int i = 0; i < size; i++) {
        cdst[i] = csrc[i];
    }
}

void mymemmove(void* dst, void* src, size_t size) {
    char* cdst = (char*) dst;
    char* csrc = (char*) src;

    char* temp = new char[size];
    for (int i = 0; i < size; i++) {
        temp[i] = csrc[i];
    }
    for (int i = 0; i < size; i++) {
        cdst[i] = temp[i];
    }
    delete[] temp;
}

void mymemmoveAdv(void* dst, void* src, size_t size) {
    char* cdst = (char*) dst;
    char* csrc = (char*) src;

    if (csrc < cdst && (csrc + size) > cdst) {
        for (int i = size - 1; i >= 0; i--) {
            cdst[i] = csrc[i];
        }
    } else {
        for (int i = 0; i < size; i++) {
            cdst[i] = csrc[i];
        }
    }
}

int main() {
    char csrc[100] = "Geeksfor";
    mymemmoveAdv(csrc + 5, csrc, strlen(csrc) + 1);
    cout<<csrc<<endl;
    return 0;
}