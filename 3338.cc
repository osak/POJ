//Name: Rectangle Cutting
//Level: 3
//Category: 塗りつぶし, 格子
//Note:

/*
 * 格子とマス目それぞれに配列の1要素づつを割り当てる。
 * DFSで塗りつぶすときは、マス目とマス目の間が壁になるので、それで繋がりを判定する
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<bool> > &cake, int ix, int iy) {
    cake[ix][iy] = false;
    int dx[] = {0, -1, 0, 1};
    int dy[] = {1, 0, -1, 0};
    for(int i = 0; i < 4; ++i) {
        int wx = ix+dx[i];
        int wy = iy+dy[i];
        if(0 <= wx && wx < cake.size() && 0 <= wy && wy < cake[0].size() && cake[wx][wy]) {
            int cx = wx+dx[i];
            int cy = wy+dy[i];
            if(0 < cx && cx < cake.size() && 0 <= cy && cy < cake[0].size() && cake[cx][cy]) dfs(cake, wx+dx[i], wy+dy[i]);
        }
    }
}

int main() {
    while(true) {
        int W, H;
        cin >> H >> W;
        if(!W && !H) break;

        vector<vector<bool> > cake(W*2+1, vector<bool>(H*2+1, true));

        int N;
        cin >> N;
        while(N--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);

            for(int x = x1*2; x <= x2*2; ++x) {
                cake[x][y1*2] = false;
                cake[x][y2*2] = false;
            }
            for(int y = y1*2; y <= y2*2; ++y) {
                cake[x1*2][y] = false;
                cake[x2*2][y] = false;
            }
        }

        int cnt = 0;
        for(int y = 1; y <= H; ++y) {
            for(int x = 1; x <= W; ++x) {
                int ix = x*2-1;
                int iy = y*2-1;
                if(cake[ix][iy]) {
                    ++cnt;
                    dfs(cake, ix, iy);
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
