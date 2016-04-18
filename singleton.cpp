#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton *getInstance();
private:
    Singleton() {}
    static Singleton* instance;
};

Singleton* Singleton::instance = 0;
Singleton* Singleton::getInstance() {
//this is not thread safe, should lock, and unlock
    if (instance == 0) {
        instance = new Singleton();
        return instance;
    } else {
        return instance;
    }
}

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    return 0;
}
