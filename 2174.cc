//Name: Decoding Task
//Level: 2
//Category: やるだけ
//Note:

/*
 * 元の文をx1 x2 x3……，鍵をk1 k2 k3……とすると，暗号文は
 * x1^k1 x2^k2 x3^k3……
 * 32^k1 x1^k2 x2^k3……
 * の二つ．同じ数字をXORすると0になることを利用し，k1 k2 k3……が求まる．
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

inline int c2n(char c) {
    if('0' <= c && c <= '9') return c-'0';
    return c-'A'+10;
}

vector<int> parse(const string &s) {
    vector<int> v;
    for(int i = 0; i < s.size(); i += 2) {
        v.push_back(c2n(s[i])*16 + c2n(s[i+1]));
    }
    
    return v;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    vector<int> v1, v2;
    v1 = parse(s1);
    v2 = parse(s2);
    
    vector<int> keys;
    keys.push_back(32 ^ v2[0]);
    for(int i = 1; i < v2.size(); ++i) {
        int x = keys[i-1] ^ v1[i-1];
        keys.push_back(x ^ v2[i]);
    }
    for(int i = 0; i < keys.size(); ++i) {
        printf("%02X", keys[i]);
    }
    puts("");

    return 0;
}
