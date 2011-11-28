#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct RoadTag {
    int to, dist, index;
    RoadTag() {}
    RoadTag(int t, int d, int i) : to(t), dist(d), index(i) {}
};

vector<vector<RoadTag> > roads;

int main() {
    int N, M;
    cin >> N >> M;
    
    roads.resize(N+1);
    for(int i = 1; i <= M; ++i) {
        int f1, f2, d;
        char c;
        cin >> f1 >> f2 >> d >> c;

        roads[f1].push_back(RoadTag(f2, d, i));
        roads[f2].push_back(RoadTag(f1, d, i));
    }

    int K;
    cin >> K;
    while(K--) {
        int from, to, limit;
        cin >> from >> to >> limit;

        priority_queue<pair<int, int> > q;
        vector<bool> used(N+1, false);

        q.push(make_pair(0, from));
        int ans = -1;
        while(!q.empty()) {
            int cost = q.top().first;
            int farm = q.top().second;
            q.pop();

            if(used[farm]) continue;
            used[farm] = true;
            if(farm == to) {
                ans = -cost;
                break;
            }

            for(int i = 0; i < roads[farm].size(); ++i) {
                if(used[roads[farm][i].to]) continue;
                if(roads[farm][i].index > limit) continue;
                q.push(make_pair(cost-roads[farm][i].dist, roads[farm][i].to));
            }
        }
        cout << ans << endl;
    }
}
