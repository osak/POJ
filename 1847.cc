//Name: Tram
//Level: 2
//Category: 最短経路,ダイクストラ,グラフ,Dijkstra,Graph
//Note:

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int> > > roads;
bool used[100];

int main() {
    int N, A, B;
    cin >> N >> A >> B;
    roads.resize(N+1);

    for(int i = 1; i <= N; ++i) {
        int k;
        cin >> k;
        for(int j = 0; j < k; ++j) {
            int to;
            cin >> to;
            roads[i].push_back(make_pair((j == 0) ? 0 : 1, to));
        }
    }

    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, A));
    while(!q.empty()) {
        int cost = q.top().first;
        int curr = q.top().second;
        q.pop();

        if(used[curr]) continue;
        used[curr] = true;
        if(curr == B) {
            cout << -cost << endl;
            break;
        }

        for(int i = 0; i < roads[curr].size(); ++i) {
            q.push(make_pair(cost-roads[curr][i].first, roads[curr][i].second));
        }
    }
    if(!used[B]) cout << -1 << endl;

    return 0;
}
