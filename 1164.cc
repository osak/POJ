#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int DC[] = { -1, 0, 1, 0 };
const int DR[] = { 0, -1, 0, 1 };

int dfs(const vector<vector<int> > &v, int r, int c, vector<vector<int> > &visited) {
    if(r < 0 ||  v.size() <= r || c < 0 || v[0].size() <= c) return 0;
    if(visited[r][c]) return 0;

    visited[r][c] = 1;
    int size = 1;
    for(int i = 0; i < 4; ++i) {
        if(!(v[r][c] & (1<<i))) {
            size += dfs(v, r+DR[i], c+DC[i], visited);
        }
    }

    return size;
}

int main() {
    ios::sync_with_stdio(0);
    int R, C;
    cin >> R >> C;

    vector<vector<int> > v(R, vector<int>(C, 0));
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            cin >> v[r][c];
        }
    }

    int maxsize = 0;
    int cnt = 0;
    vector<vector<int> > visited(R, vector<int>(C, 0));
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(!visited[r][c]) {
                int size = dfs(v, r, c, visited);
                maxsize = max(size, maxsize);
                ++cnt;
            }
        }
    }

    cout << cnt << endl;
    cout << maxsize << endl;

    return 0;
}
