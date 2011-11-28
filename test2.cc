#include <iostream>

using namespace std;

struct test {
    int a[2];
};

int main() {
    test t1, t2;
    t1.a[0] = t2.a[0] = 1;
    t1.a[1] = t2.a[1] = 2;

    cout << (t1==t2) << endl;
    return 0;
}
