//Name: Parencodings
//Level: 2
//Category: シミュレーション,再帰的構造
//Note: Golf向き

/*
 * P-Sequenceをカッコの列に複合してから、改めてW-Sequenceを算出する。
 * 再帰的構造に注意する。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> w(N, 0);

        string s;
        int prevp = 0;
        while(N--) {
            int p;
            cin >> p;

            for(int i = prevp; i < p; ++i) s += '(';
            s += ')';
            prevp = p;
        }

        int level = 0;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(') w[++level] = 0;
            else {
                cout << w[level]+1 << ' ';
                w[level-1] += w[level]+1;
                --level;
            }
        }
        cout << endl;
    }
    return 0;
}
