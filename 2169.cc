//Name: Kingdom of Magic
//Level: 2
//Category: グラフ,Graph,ダイクストラ法,Dijkstra,Special Judge
//Note:

/*
 * 二人の場所のペアをノードにしてダイクストラするだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

struct Tag {
    pair<int,int> pos;
    int cost;

    Tag(const pair<int,int> &p, int c) : pos(p), cost(c) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    pair<int,int> init, goal;
    cin >> N >> M >> init.first >> init.second >> goal.first >> goal.second;
    --init.first; --init.second;
    --goal.first; --goal.second;

    vector<vector<int> > v(N, vector<int>(N, 0));
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        v[a-1][b-1] = v[b-1][a-1] = true;
    }
    for(int i = 0; i < N; ++i) {
        v[i][i] = true;
    }

    vector<vector<int> > memo(N, vector<int>(N, 100*100*100));
    vector<vector<pair<int,int> > > prev(N, vector<pair<int,int> >(N));
    priority_queue<Tag> q;
    q.push(Tag(init, 0));
    while(!q.empty()) {
        Tag cur = q.top();
        q.pop();

        if(cur.pos == goal) {
            break;
        }
        if(memo[cur.pos.first][cur.pos.second] < cur.cost) continue;
        memo[cur.pos.first][cur.pos.second] = cur.cost;

        for(int ai = 0; ai < N; ++ai) {
            if(!v[cur.pos.first][ai]) continue;
            for(int bi = 0; bi < N; ++bi) {
                if(!v[cur.pos.second][bi]) continue;
                if(!v[ai][bi]) continue;
                if(ai == bi) continue;
                if(make_pair(ai, bi) == cur.pos) continue;
                if(make_pair(bi, ai) == cur.pos) continue;

                int nc = cur.cost;
                if(ai != cur.pos.first) ++nc;
                if(bi != cur.pos.second) ++nc;
                if(memo[ai][bi] > nc) {
                    memo[ai][bi] = nc;
                    prev[ai][bi] = cur.pos;
                    q.push(Tag(make_pair(ai, bi), nc));
                }
            }
        }
    }

    vector<pair<int,int> > route;
    pair<int,int> cur = goal;
    while(cur != init) {
        route.push_back(cur);
        cur = prev[cur.first][cur.second];
    }
    route.push_back(init);

    cout << memo[goal.first][goal.second] << ' ' << route.size() << endl;
    for(vector<pair<int,int> >::reverse_iterator it = route.rbegin(); it != route.rend(); ++it) {
        cout << it->first+1 << ' ' << it->second+1 << endl;
    }

    return 0;
}
