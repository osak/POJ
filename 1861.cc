#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Route {
    int from, to, cost;
};

bool operator < (const Route &r1, const Route &r2) {
    return r2.cost<r1.cost;
}

int costs[1001][1001];
bool used[1001];

int main() {
    int n, m;
    cin >> n >> m;
    while(m--) {
        int a, b, cost;
        cin >> a >> b >> cost;
        costs[a][b] = costs[b][a] = cost;
    }

    //First node is 1
    int maxcost = 0;
    priority_queue<Route> q;
    for(int i = 1; i <= n; ++i) {
        if(costs[1][i] != 0) {
            Route r;
            r.from = 1;
            r.to = i;
            r.cost = costs[1][i];
            q.push(r);
        }
    }
    used[1] = true;
    vector<Route> routes;
    for(int j = 2; j <= n; ++j) {
        Route r;
        do {
            r = q.top();
            q.pop();
        } while(used[r.to]);
        routes.push_back(r);
        used[r.to] = true;
        if(maxcost < r.cost) maxcost = r.cost;
        for(int i = 1; i <= n; ++i) {
            if(used[i]) continue;
            if(costs[r.from][i] != 0) {
                Route r2;
                r2.from = r.from; 
                r2.to = i; 
                r2.cost = costs[r.from][i];
                q.push(r2);
                cout << r2.from << " " << r2.to << endl;
            }
        }
    }
    cout << maxcost << endl;
    cout << routes.size() << endl;
    for(int i = 0; i < routes.size(); ++i) {
        cout << routes[i].from << " " << routes[i].to << endl;
    }

    return 0;
}
