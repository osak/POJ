//Name: SHAKE
//Level: 3
//Category: 実装
//Note:

/*
 * RとSは普通にローテートすればよい．
 * Lは左上隅を起点としたとき，一辺の長さが簡単に計算できるので
 * その長さだけ移動したら方向転換するようにしてローテートする．
 * ゴールは座標で見てもよいが，回転方向の違いで補正するのが面倒なので
 * 一周にかかるステップ数を計算している．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static const int dt[2][4][2] = {
    {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    },
    {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    },

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string cmd;
    while(cin >> cmd) {
        string str;
        cin.ignore();
        getline(cin, str);

        int size = (cmd[0]-'0')*10 + (cmd[1]-'0');
        if(size == 0) size = 100;
        vector<vector<char> > matrix(size, vector<char>(size));

        if(str.size() < size*size) {
            int rem = size*size - str.size();
            for(int i = 0; i < rem; ++i) {
                str += 'A' + i%26;
            }
        }

        for(int r = 0; r < size; ++r) {
            for(int c = 0; c < size; ++c) {
                matrix[r][c] = toupper(str[r*size+c]);
            }
        }

        for(string::iterator it = cmd.begin()+2; it != cmd.end(); ++it) {
            if(*it == 'R') {
                for(int r = 0; r < size; ++r) {
                    if(r % 2 == 0) { // Shift Left
                        char tmp = matrix[r][size-1];
                        for(int c = size-1; c > 0; --c) {
                            matrix[r][c] = matrix[r][c-1];
                        }
                        matrix[r][0] = tmp;
                    }
                    else { // Shift Right
                        char tmp = matrix[r][0];
                        for(int c = 0; c < size-1; ++c) {
                            matrix[r][c] = matrix[r][c+1];
                        }
                        matrix[r][size-1] = tmp;
                    }
                }
            }
            else if(*it == 'S') {
                for(int c = 0; c < size; ++c) {
                    if(c % 2 == 0) { // Shift Up
                        char tmp = matrix[0][c];
                        for(int r = 0; r < size-1; ++r) {
                            matrix[r][c] = matrix[r+1][c];
                        }
                        matrix[size-1][c] = tmp;
                    }
                    else { // Shift Down
                        char tmp = matrix[size-1][c];
                        for(int r = size-1; r > 0; --r) {
                            matrix[r][c] = matrix[r-1][c];
                        }
                        matrix[0][c] = tmp;
                    }
                }
            }
            else if(*it == 'L') {
                for(int sr = 0; sr < size/2; ++sr) {
                    int inf = sr, sup = size-sr;
                    int pat = sr%2, idx = 0;
                    char tmp = matrix[sr][sr];
                    int r = sr, c = sr;

                    // 一辺*4 - 角
                    // 最後の-1はスタートに戻る直前で止めるため．
                    for(int step = 0; step < (sup-inf)*4-4-1; ++step) {
                        int nr = r + dt[pat][idx][0], nc = c + dt[pat][idx][1];
                        matrix[r][c] = matrix[nr][nc];
                        if((r != nr && (nr == inf || nr+1 == sup)) ||
                           (c != nc && (nc == inf || nc+1 == sup))) 
                        {
                            ++idx;
                        }
                        r = nr;
                        c = nc;
                    }
                    matrix[r][c] = tmp;
                }
            }
        }

        for(int r = 0; r < size; ++r) {
            for(int c = 0; c < size; ++c) {
                cout << matrix[r][c];
            }
        }
        cout << endl;
    }

    return 0;
}
