//Name: ID Codes
//Level: 1
//Category: 順列,やるだけ
//Note:

/*
 * next_permutationに突っ込むだけ。
 * next_permutationは、最大の順列を与えた時だけfalseを返すことに注意。
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    while(true) {
        string str;
        cin >> str;
        if(str == "#") break;

        if(next_permutation(str.begin(), str.end())) {
            cout << str << endl;
        }
        else {
            cout << "No Successor" << endl;
        }

    }

    return 0;
}
