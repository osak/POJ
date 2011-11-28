//Name: IMMEDIATE DECODABILITY
//Level: 1
//Category: 文字列比較,やるだけ
//Note:

/*
 * やるだけ。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    for(int C = 1; ; ++C) {
        vector<string> v;
        while(true) {
            string s;
            cin >> s;
            if(s == "9") break;
            if(cin.eof()) return 0;
            v.push_back(s);
        }
        sort(v.begin(), v.end());
        bool ok = true;
        for(int i = 0; i < v.size(); ++i) {
            for(int j = i+1; j < v.size(); ++j) {
                if(v[i] == v[j].substr(0, v[i].size())) {
                    ok = false;
                    goto endloop;
                }
            }
        }
endloop:
        cout << "Set " << C << " is " << (ok?"":"not ") << "immediately decodable" << endl;
    }
    return 0;
}
