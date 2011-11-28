//Name: The Separator in Grid
//Level: 2
//Category: グラフ,Graph,幅優先探索,BFS
//Note:

/*
 * 問題の条件から，新しいセパレータとして存在できるのは最初のセパレータとその右のマスだけ．
 * (既存のセパレータは黒にできない→右にしか移動できない
 *  追加したセパレータは白にできない→2マス以上の移動はできない)
 * したがって，これらのマスで最短経路を求めればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};

struct Tag {
    int r, c;
    int cost;

    Tag(int r, int c, int co) : r(r), c(c), cost(co) {}
};

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int R, C;
        cin >> R >> C;
        if(!R && !C) break;

        vector<string> field(R);
        for(int i = 0; i < R; ++i) {
            cin >> field[i];
            for(int j = C-1; j >= 1; --j) {
                if(field[i][j-1] == 'S') {
                    field[i][j] = 'S';
                    break;
                }
            }
        }

        int ans = 0;
        queue<Tag> q;
        vector<vector<int> > visited(R, vector<int>(C, 0));
        for(int c = 0; c < C; ++c) {
            if(field[0][c] == 'S') {
                q.push(Tag(0, c, 1));
                visited[0][c] = true;
            }
        }
        while(!q.empty()) {
           Tag t = q.front();
           q.pop();

           if(t.r == R-1) {
               ans = t.cost;
               break;
           }

           for(int i = 0; i < 4; ++i) {
               int nr = t.r + DR[i];
               int nc = t.c + DC[i];
               if(nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
               if(field[nr][nc] != 'S') continue;
               if(visited[nr][nc]) continue;
               visited[nr][nc] = true;
               q.push(Tag(nr, nc, t.cost+1));
           }
        }

        cout << ans << endl;
    }
    return 0;
}
