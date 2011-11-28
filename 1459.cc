//Name: Power Network
//Level: 2
//Category: Maximum Flow,最大流,Graph,グラフ
//Note:

/*
 * 最大流やるだけ。
 * relabel_to_frontを用いた解法。
 * 実装等はIntroduction to algorithmsの26.5を参照。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>
#include <list>

using namespace std;

void relabel_to_front(const vector<vector<int> > &capacity, vector<vector<int> > &flow) {
    int N = (int)capacity.size() - 2;
    vector<vector<int> > neighbors(N+2);

    for(int u = 0; u < N+2; ++u) 
        for(int v = 0; v < N+2; ++v) 
            if(capacity[u][v] > 0) {
                neighbors[u].push_back(v);
                neighbors[v].push_back(u);
            }

    vector<int> height(N+2, 0);
    vector<int> excess(N+2, 0);
    height[0] = N+2;
    height[N+1] = 0;
    for(int i = 1; i <= N; ++i)
        if(capacity[0][i] > 0) {
            excess[i] = flow[0][i] = capacity[0][i];
            flow[i][0] = -capacity[0][i];
        }

    list<int> q;
    for(int i = 1; i <= N; ++i) q.push_back(i);

    list<int>::iterator it = q.begin();
    while(it != q.end()) {
        int u = *it;

        //Discharge
        int old_height = height[u];
        while(excess[u] > 0) {
            for(int i = 0; excess[u] > 0 && i < neighbors[u].size(); ++i) {
                int v = neighbors[u][i];
                if(capacity[u][v]-flow[u][v] > 0 && height[u] == height[v]+1) {
                    int d = min(excess[u], capacity[u][v] - flow[u][v]);
                    excess[u] -= d;
                    excess[v] += d;
                    flow[u][v] += d;
                    flow[v][u] = -flow[u][v];
                }
            }
            if(excess[u] > 0) {
                //Relabel
                height[u] = INT_MAX;
                for(int i = 0; i < neighbors[u].size(); ++i) {
                    int v = neighbors[u][i];
                    if(capacity[u][v] - flow[u][v] > 0) height[u] = min(height[u], height[v]+1);
                }
            }
        }
        if(height[u] > old_height) {
            q.erase(it);
            q.push_front(u);
            it = q.begin();
        }
        ++it;
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
            if(u != v) capacity[u][v] = z;
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

        relabel_to_front(capacity, flow);

        int sum = 0;
        for(int i = 0; i < N+1; ++i) sum += flow[0][i];
        cout << sum << endl;
    }
}
