//Name: Polynomial Showdown
//Level: 2
//Category: 実装
//Note:

/*
 * パターンは問題文で全て説明されているので，その通りに条件を分けていけばよい．
 * 0を出力するパターンに注意．
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int main() {
    string line;
    while(getline(cin, line)) {
        vector<int> coefs;
        istringstream is(line);
        while(!is.eof()) {
            int c;
            is >> c;
            coefs.push_back(c);
        }
        int N = coefs.size();
        bool first = true;
        for(int i = 0; i < N; ++i) {
            if(coefs[i] == 0) continue;
            if(coefs[i] < 0) {
                if(first) cout << "-";
                else cout << " - ";
            }
            else if(!first) cout << " + ";
            if(i == N-1 || abs(coefs[i]) != 1) cout << abs(coefs[i]);

            if(i != N-1) cout << "x";
            if(i < N-2) cout << "^" << (N-i-1);

            first = false;
        }
        if(first) cout << "0";
        cout << endl;
    }
    return 0;
}

