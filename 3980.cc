//Name: 取模运算
//Level: 1
//Category: やるだけ
//Note: ios::sync_with_stdio(0)やらないとeof取れない？

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    int a, b;
    while(cin >> a >> b) {
        cout << a%b << endl;
    }
    return 0;
}
