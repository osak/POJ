#include <iostream>
#include <vector>

using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

int fill(vector<vector<int> > &v, int x, int y, int num) {
    int W = v.size();
    int H = v[0].size();

    int cnt = 0;

    v[x][y] = 0;
    for(int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(0 <= xx && xx < W && 0 <= yy && y < H) {
            if(v[xx][yy] == num) cnt += fill(v, xx, yy, num);
        }
    }
    return cnt+1;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<vector<int> > v(N, vector<int>(N, N));
        for(int i = 1; i <= N-1; ++i) {
            for(int j = 0; j < N; ++j) {
                int x, y;
                cin >> x >> y;
                --x; --y;
                v[x][y] = i;
            }
        }

        bool ok = true;
        for(int x = 0; x < N; ++x) {
            for(int y = 0; y < N; ++y) {
                if(v[x][y] == 0) continue;
                int cnt = fill(v, x, y, v[x][y]);
                if(cnt != N) {
                    ok = false;
                    goto end;
                }
            }
        }
end:
        if(ok) cout << "good" << endl;
        else cout << "wrong" << endl;
    }
    return 0;
}
