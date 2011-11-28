#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int field[36][36];
long long path[36][36];

int main() {
    while(true) {
        int n;
        cin >> n;
        if(n == -1) break;
        memset(field, 0, sizeof(int)*36*36);
        memset(path, 0, sizeof(long long)*36*36);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%1d", &field[i][j]);
            }
        }

        path[1][1] = 1;
        for(int x = 1; x <= n; ++x) {
            for(int y = 1; y <= n; ++y) {
                int num = field[x][y];
                if(num == 0) continue;
                int px = x+num;
                if(px <= n) path[px][y] += path[x][y];
                int py = y+num;
                if(py <= n) path[x][py] += path[x][y];
            }
        }

        cout << path[n][n] << endl;
    }

    return 0;
}
