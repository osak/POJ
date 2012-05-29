//Name: The Game of Efil
//Level: 3
//Category: シミュレーション,全探索
//Note: ancestorsとあるが，1世代だけ考えればよい

/*
 * 最大で16マスしかないので，初期状態2^16通り全て試す．
 *
 * 問題文にparentとancestorのふたつの単語が出てくるので，ある状態に到達し得る
 * 全ての状態を求めるのかと思いきや，直接の親だけを数えればいいらしい……
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void decode(int pattern, vector<vector<int> > &field) {
    for(int r = 0; r < (int)field.size(); ++r) {
        for(int c = 0; c < (int)field[r].size(); ++c) {
            field[r][c] = pattern&1;
            pattern >>= 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int CASE = 1; ; ++CASE) {
        int R, C;
        cin >> R >> C;
        if(!R && !C) break;

        vector<vector<int> > goal(R, vector<int>(C, 0)), field(R, vector<int>(C, 0));
        int N;
        cin >> N;
        for(int i = 0; i < N; ++i) {
            int r, c;
            cin >> r >> c;
            goal[r][c] = 1;
        }

        int ans = 0;
        for(int pat = 0; pat < 1<<(R*C); ++pat) {
            decode(pat, field);
            for(int r = 0; r < R; ++r) {
                for(int c = 0; c < C; ++c) {
                    int neighbors = 0;
                    for(int dr = -1; dr <= 1; ++dr) {
                        for(int dc = -1; dc <= 1; ++dc) {
                            if(dr == 0 && dc == 0) continue;
                            int nr = (r+dr+R) % R;
                            int nc = (c+dc+C) % C;
                            neighbors += field[nr][nc];
                        }
                    }
                    int next_cell = 0;
                    if((field[r][c] && (neighbors == 2 || neighbors == 3)) ||
                       (!field[r][c] && neighbors == 3))
                    {
                        next_cell = 1;
                    }
                    if(goal[r][c] != next_cell) goto next;
                }
            }
            ++ans;
next:
            ;
        }

        cout << "Case " << CASE << ": ";
        if(ans) cout << ans << " possible ancestors." << endl;
        else cout << "Garden of Eden." << endl;
    }

    return 0;
}
