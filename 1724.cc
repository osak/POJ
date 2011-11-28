#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct Road {
    int to, len, cost;

    Road() {}
    Road(int t, int l, int c) : to(t), len(l), cost(c) {}
};

bool operator <(const Road &r1, const Road &r2) {
    if(r1.len != r2.len) return r2.len < r1.len;
    return r2.cost < r1.cost;
}

typedef pair<int,int> Path;

Path costs[101][101];
Path minval[101];
int K, N;

int main() {
    int r;
    cin >> K >> N >> r;
    while(r--) {
        int s, d, l, t;
        cin >> s >> d >> l >> t;
        costs[s][d] = make_pair(l, t);
    }
    for(int i = 1; i <= N; ++i) {
        minval[i] = make_pair(INT_MAX, INT_MAX);
    }

    priority_queue<Road> q;
    //Start from city 1
    for(int i = 1; i <= N; ++i) {
        if(costs[1][i].first != 0) {
            Road r(i, costs[1][i].first, costs[1][i].second);
            q.push(r);
        }
    }
    minval[1] = make_pair(0, 0);

    int minlen = INT_MAX;
    while(!q.empty()) {
        Road r = q.top();
        q.pop();
        if(minval[r.to].first > r.len) {
            minval[r.to].first = r.len;
        }
        if(minval[r.to].second > r.cost) {
            minval[r.to].second = r.cost;
        }

        for(int i = 1; i <= N; ++i) {
            if(costs[r.to][i].first == 0) continue;

            int len = r.len + costs[r.to][i].first;
            int cost = r.cost + costs[r.to][i].second;
            if(cost > K) continue;
            if(len >= minval[i].first) {
                if(cost >= minval[i].second) {
                    continue;
                }
            }
            Road r2(i, len, cost);
            q.push(r2);
        }
    }

    if(minval[N].first == INT_MAX) cout << -1 << endl;
    else cout << minval[N].first << endl;
    return 0;
}
