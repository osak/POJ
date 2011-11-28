#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct City {
    int n, len, cost;
    City() {}
    City(int nn, int ll, int cc) : n(nn), len(ll), cost(cc) {}
};

bool operator < (const City &c1, const City &c2) {
    if(c1.len != c2.len) return c2.len < c1.len;
    else return c2.cost < c1.cost;
}

pair<int, int> citymap[101][101];
pair<int, int> minval[101];
bool used[101][10001];

int main() {
    int K, N, R;
    cin >> K >> N >> R;

    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j) 
            citymap[i][j] = make_pair(INT_MAX, INT_MAX);
    while(R--) {
        int s, d, l, t;
        cin >> s >> d >> l >> t;
        citymap[s][d] = make_pair(l, t);
    }

    for(int i = 1; i <= N; ++i) {
        minval[i] = make_pair(INT_MAX, INT_MAX);
    }

    priority_queue<City> q;
    City c(1, 0, 0);
    q.push(c);
    minval[1] = make_pair(0, 0);

    while(!q.empty()) {
        City city = q.top();
        q.pop();

        if(city.n == N) {
            cout << city.len << endl;
            return 0;
        }
        used[city.n][city.cost] = true;
        for(int i = 1; i <= N; ++i) {
            if(citymap[city.n][i].first == INT_MAX) continue;

            int len = city.len + citymap[city.n][i].first;
            int cost = city.cost + citymap[city.n][i].second;
            if(cost > K) continue;

            if(!used[i][cost]) {
                City c(i, len, cost);
                q.push(c);
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
