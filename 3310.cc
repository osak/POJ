#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool valid(const vector<vector<bool> > &v, vector<bool> &used, int node, int from) {
    used[node] = true;
    for(int i = 0; i < v[node].size(); ++i) {
        if(v[node][i]) {
            if(i != from && used[i]) return false;
            if(used[i]) continue;
            if(!valid(v, used, i, node)) return false;
        }
    }
    return true;
}

int main() {
    for(int C = 1; ; ++C) {
        int N, M;
        cin >> N;
        if(!N) break;
        cin >> M;

        vector<vector<bool> > v(N, vector<bool>(N, false));
        vector<int> existcnt(N, 0);
        for(int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            v[a][b] = v[b][a] = true;
            existcnt[a]++;
            existcnt[b]++;
        }

        bool ok = true;
        vector<bool> used(N, false);
        if(!valid(v, used, 0, -1)) ok = false;
        for(int i = 0; i < N; ++i) {
            if(!used[i]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            vector<pair<int, int> > path;
            for(int i = 0; i < N; ++i) {
                for(int j = i; j < N; ++j) {
                    if(v[i][j]) {
                        if(existcnt[i] > 1 && existcnt[j] > 1) path.push_back(make_pair(i, j));
                    }
                }
            }

            vector<int> cnt(N, 0);
            for(int i = 0; i < path.size(); ++i) {
                cnt[path[i].first]++;
                cnt[path[i].second]++;
            }

            int one = 0;
            for(int i = 0; i < N; ++i) {
                if(cnt[i] == 1) ++one;
                if(cnt[i] > 2) {
                    ok = false;
                }
            }
        }

        cout << "Graph " << C << " is " << (ok?"":"not ") << "a caterpillar." << endl;
    }
    return 0;
}
