//Name: Chessboard Dance
//Level: 2
//Category: シミュレーション,やるだけ
//Note:

/*
 * 単純なシミュレーション。
 * 駒を押す時は、先に終端を求める必要があることに注意。
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

inline bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

int main() {
    while(true) {
        vector<string> field(8);
        for(int i = 0; i < 8; ++i) cin >> field[i];
        if(field[0] == "--") break;

        int dir = 0;
        int x, y;
        for(y = 0; y < 8; ++y) {
            for(x = 0; x < 8; ++x) {
                if(field[y][x] == '^') {
                    dir = 0;
                    goto endpos;
                }
                if(field[y][x] == '<') {
                    dir = 1;
                    goto endpos;
                }
                if(field[y][x] == 'v') {
                    dir = 2;
                    goto endpos;
                }
                if(field[y][x] == '>') {
                    dir = 3;
                    goto endpos;
                }
            }
        }

endpos:
        field[y][x] = '.';
        while(true) {
            string cmd, arg;
            cin >> cmd;
            if(cmd == "#") break;
            cin >> arg;

            if(cmd == "move") {
                int n = atoi(arg.c_str());
                while(n--) {
                    int px = x + dx[dir];
                    int py = y + dy[dir];
                    if(!inRange(0, py, 7) || !inRange(0, px, 7)) break;
                    while(inRange(0, py, 7) && inRange(0, px, 7) && field[py][px] != '.') {
                        px += dx[dir];
                        py += dy[dir];
                    }
                    px = min(7, max(0, px));
                    py = min(7, max(0, py));
                    for(; px != x || py != y; px -= dx[dir], py -= dy[dir]) {
                        field[py][px] = field[py-dy[dir]][px-dx[dir]];
                    }
                    x += dx[dir];
                    y += dy[dir];
                }
            }
            else if(cmd == "turn") {
                if(arg == "left") dir = (dir+1) % 4;
                else if(arg == "right") dir = (dir+3) % 4;
                else dir = (dir+2) % 4;
            }
        }

        field[y][x] = "^<v>"[dir];
        for(int i = 0; i < 8; ++i) cout << field[i] << endl;
        cout << endl;
    }
    return 0;
}
