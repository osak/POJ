//Name: Snap
//Level: 2
//Category: シミュレーション
//Note: 標準ライブラリのrandを使っているため，ローカルではテストが面倒．srandしないで投げれば通る．

/*
 * シミュレーションするだけ．
 * rand()の定義が書いていないが，srandしないで投げれば通るようにできているらしい．
 * glibc2.14では少なくとも通らない．
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    string down[2], up[2];
    down[0] = s1;
    down[1] = s2;
    up[0] = up[1] = "";

    int winner = -1;
    for(int i = 0; i < 1000; ++i) {
        for(int j = 0; j < 2; ++j) {
            up[j] = down[j][0] + up[j];
        }
        if(down[0][0] == down[1][0]) {
            int snap = rand()/99 % 2;
            up[snap] = up[1-snap] + up[snap];
            up[1-snap] = "";
            cout << "Snap! for " << (snap==0?"Jane":"John") << ": " << up[snap] << endl;
        }
        for(int j = 0; j < 2; ++j) {
            down[j].erase(0,1);
            if(down[j].size() == 0) {
                down[j] = up[j];
                if(down[j].size() == 0) {
                    winner = 1-j;
                    goto end;
                }
                reverse(down[j].begin(), down[j].end());
                up[j] = "";
            }
        }
    }
end:
    if(winner == -1) cout << "Keeps going and going ..." << endl;
    else cout << (winner==0?"Jane":"John") << " wins." << endl;

    return 0;
}
