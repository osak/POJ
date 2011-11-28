#include <iostream>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

bool used[300][300][2];
int disttable[2][300][300];

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == 0) break;

        pair<int, int> pos[300];
        int minval[300];
        for(int i = 0; i < N; ++i) {
            cin >> pos[i].first >> pos[i].second;
            minval[i] = INT_MAX;
        }
        memset(used, 0, sizeof(used));

        //(Cost, Which), (Left limit, Right limit)
        priority_queue<pair<pair<int,int> pair<int,int> > > q;
        q.push(make_pair(make_pair(0, 0), make_pair(0, 0)));

        while(!q.empty()) {
            int cost = q.top().first;
            int l = q.top().second.first;
            int r = q.top().second.second;
            q.pop();

            if(l == r && cost < 0) {
                if(minval[l] > -cost) minval[l] = -cost;
                cout << l << ":" << -cost << endl;
                continue;
            }
            if(used[l][r]) continue;
            if(cost < 0) used[l][r] = true;

            int load = 0;
            for(int i = (l+1)%N; i != r; i = (i+1)%N) {
                load += pos[i].first;
            }
            int nl = (l+1) % N;
            int nr = (r-1+N) % N;
            q.push(make_pair(cost-load*pos[l].second, make_pair(nl, r)));
            q.push(make_pair(cost-load*pos[nr].second, make_pair(l, nr)));
        }
        int best = INT_MAX;
        for(int i = 0; i < N; ++i) {
            if(minval[i] < best) best = minval[i];
        }
        cout << best << endl;
    }
    return 0;
}
