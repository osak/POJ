//Name: String Matching
//Level: 2
//Category: 文字列比較
//Note:

/*
 * 片方の文字列を1文字ずつずらしながら比較していけば良い。
 * インデックスの取り方に注意。範囲外アクセスや端の数え忘れはありがち。
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if(a < b) return gcd(b, a);
    while(b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    while(true) {
        string str1, str2;
        cin >> str1 >> str2;
        if(str1 == "-1") break;

        vector<int> charpos[26];
        for(int i = 0; i < str1.length(); ++i) {
            charpos[str1[i]-'A'].push_back(i);
        }

        int bestcnt = 0;
        for(int i = 0; i < str2.length(); ++i) {
            int idx = str2[i]-'A';
            if(charpos[idx].empty()) continue;
            for(int j = 0; j < charpos[idx].size(); ++j) {
                int s1p = charpos[idx][j];
                int cnt = 0;
                for(int k = 0; (i+k)<str2.length() && (s1p+k)<str1.length(); ++k) {
                    if(str1[s1p+k] == str2[i+k]) ++cnt;
                }
                if(cnt > bestcnt) bestcnt = cnt;
            }
        }

        int len = str1.length() + str2.length();
        bestcnt *= 2;

        cout << "appx(" << str1 << "," << str2 << ") = ";
        if(len == bestcnt) {
            cout << 1 << endl;
        }
        else if(bestcnt == 0) {
            cout << 0 << endl;
        }
        else {
            int g = gcd(len, bestcnt);
            cout << bestcnt/g << "/" << len/g << endl;
        }
    }
    return 0;
}
