//Name: Power Network
//Level: 2
//Category: Maximum Flow,最大流,Graph,グラフ
//Note:

/*
 * 最大流やるだけ。
 * Edmonds_Karp法(O(VE^2))による解法。
 * 実装等はIntroduction to Algorithmsの26.2を参照。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

//edmonds_carpのヘルパー
bool find_augment_path(const vector<vector<int> > &capacity, const vector<vector<int> > &flow, vector<int> &augment_path) {
    int N = (int)capacity.size() - 2;
    queue<int> q;
    vector<int> prev(N+2, -1);
    q.push(0);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == N+1) {
            int pos = 0;
            int v = N+1;
            while(v != -1) {
                augment_path[pos++] = v;
                v = prev[v];
            }
            reverse(augment_path.begin(), augment_path.begin()+pos);
            return true;
        }
        //Sourceへは行かないようにする
        for(int i = 1; i < N+2; ++i) {
            if(prev[i] != -1) continue;
            if(capacity[u][i] - flow[u][i] > 0) {
                prev[i] = u;
                q.push(i);
            }
        }
    }
    return false;
}

//ノード[0]がSource, [N+1]がTerminal
void edmonds_carp(const vector<vector<int> > &capacity, vector<vector<int> > &flow) {
    int N = (int)capacity.size() - 2;
    vector<int> augment_path(N+2, -1);
    while(find_augment_path(capacity, flow, augment_path)) {
        int aug = INT_MAX;
        for(int i = 0; augment_path[i] != N+1; ++i)
            aug = min(aug, capacity[augment_path[i]][augment_path[i+1]] - flow[augment_path[i]][augment_path[i+1]]);
        for(int i = 0; augment_path[i] != N+1; ++i) {
            int u = augment_path[i], v = augment_path[i+1];
            flow[u][v] += aug;
            flow[v][u] = -flow[u][v];
        }
    }
}

int main() {
    int N, NP, NC, M;
    while(cin >> N >> NP >> NC >> M) {
        //Source: 0
        //Terminal: N+1
        vector<vector<int> > capacity(N+2, vector<int>(N+2, 0));
        vector<vector<int> > flow(N+2, vector<int>(N+2, 0));

        for(int i = 0; i < M; ++i) {
            char lp, comma, rp;
            int u, v, z;
            cin >> lp >> u >> comma >> v >> rp >> z;
            ++u; ++v;
            capacity[u][v] = z;
        }
        for(int i = 0; i < NP; ++i) {
            char lp, rp;
            int u, z;
            cin >> lp >> u >> rp >> z;
            ++u;
            capacity[0][u] = z;
        }
        for(int i = 0; i < NC; ++i) {
            char lp, rp;
            int u, z;
            cin >> lp >> u >> rp >> z;
            ++u;
            capacity[u][N+1] = z;
        }

        edmonds_carp(capacity, flow);

        int sum = 0;
        for(int i = 0; i < N+1; ++i) sum += flow[0][i];
        cout << sum << endl;
    }
}
