//Name: Byte Me!
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

/*
 * やるだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int decode(const string &binstr) {
    int val = 0;
    for(string::const_iterator it = binstr.begin(); it != binstr.end(); ++it) {
        val <<= 1;
        val += *it-'0';
    }
    return val;
}

int read_hand() {
    string str;
    cin >> str;
    return decode(str);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string cmd;
        cin >> cmd;
        if(cmd == "ENDOFINPUT") break;

        int N;
        cin >> N;

        int cur = read_hand() + read_hand();
        int maxval = 0, realmax = 0;
        for(int i = 0; i < N; ++i) {
            int v = read_hand() + 255;
            if(v <= 510) {
                realmax = max(realmax, v);
            }

            if(v > 510) v = 510;
            maxval = max(maxval, v);
        }

        queue<int> bytes, nibbles;
        for(int i = 0; i < 4; ++i) {
            bytes.push(read_hand());
        }
        for(int i = 0; i < 4; ++i) {
            nibbles.push(read_hand());
        }
        cin >> cmd; // ignore "END"

        cout << "HAND " << N << endl;
        for(int i = 0; i < 4; ++i) {
            if(cur > maxval) break;
            if(cur < 382) {
                cout << "Byte me!" << endl;
                cur += bytes.front();
                bytes.pop();
            }
            else if(cur <= 500) {
                cout << "Nibble me!" << endl;
                cur += nibbles.front();
                nibbles.pop();
            }
        }

        if(cur > 510) {
            cout << "Bust!" << endl;
        }
        else if(cur >= realmax) {
            cout << "Win!" << endl;
        }
        else {
            cout << "Lose!" << endl;
        }
    }

    return 0;
}
