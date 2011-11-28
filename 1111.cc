//Name: Image Perimeters
//Level: 2
//Category: 塗りつぶし,探索
//Note:

/*
 * Xを塗りつぶしながら、周囲4マスにXがあるかどうかをチェックして
 * 周長を求める。
 */
#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

typedef pair<int, int> Point;

char field[22][22];
int ax[] = {0, 0, 1, -1};
int ay[] = {1, -1, 0, 0};

int main() {
    while(true) {
        int w, h, x, y;
        cin >> h >> w >> y >> x;

        if(w == 0) break;
        memset(field, '.', 22*22*sizeof(char));
        for(int yy = 1; yy <= h; ++yy) {
            cin >> &field[yy][1];
        }

        queue<Point> q;
        int len = 0;
        q.push(make_pair(x, y));
        while(!q.empty()) {
            Point p = q.front();
            q.pop();
            x = p.first;
            y = p.second;
            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    if(field[y+dy][x+dx] != 'X') continue;
                    field[y+dy][x+dx] = '@';
                    q.push(make_pair(x+dx, y+dy));
                    for(int i = 0; i < 4; ++i) {
                        char c = field[y+dy+ay[i]][x+dx+ax[i]];
                        if(c == '.' || c == '\0') {
                            ++len;
                        }
                    }
                }
            }
        }
        cout << len << endl;
    }
    return 0;
}
