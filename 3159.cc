#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<vector<pair<int, int> > > costs;
vector<bool> used(0, false);

int abs_(int n) {
    return n<0 ? -n : n;
}

int main() {
    int N, M;
    cin >> N >> M;

    costs.resize(N+1);
    for(int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        costs[a].push_back(make_pair(c, b));
        //costs[b].push_back(make_pair(-c, a));
    }

    vector<int> dist(N, INT_MIN);
    queue<pair<int, int> > q;
    dist[1] = 0;
    for(int k = 0; k < costs[1].size(); ++k) {
        q.push(make_pair(1, costs[1][k].second));
    }
    while(!q.empty()) {
        int from = q.front().first;
        int to = q.front().second;
        q.pop();

        if(dist[from] + costs[from][to].first > dist[to]) {
            dist[to] = dist[from] + costs[from][to].first;
            for(int k = 0; k < costs[to].size(); ++k) {
                q.push(make_pair(to, costs[to][k].second));
            }
        }
    }

    cout << abs_(dist[N]-dist[1]) << endl;

    return 0;
}
