#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Tag {
    int a, b, w;

    Tag() {}
    Tag(int a, int b, int w) : a(a), b(b), w(w) {}
};

int best_cost;
vector<int> best_hist;

int dfs(const vector<vector<pair<int, int> > > &edges, int pos, int cost, vector<int> &used, vector<int> &hist) {

    if(pos == edges.size()-1 && cost > best_cost) {
        best_cost = cost;
        best_hist = hist;
        return cost;
    }

    int maxcost = 0;
    used[pos] = true;
    hist.push_back(pos);
    for(int i = 0; i < edges[pos].size(); ++i) {
        const pair<int,int> &p = edges[pos][i];
        if(used[p.first]) continue;

        int tmp = dfs(edges, p.first, cost + p.second, used, hist);
        if(tmp > maxcost) {
            maxcost = tmp;
        }
    }
    hist.pop_back();
    used[pos] = false;
    return maxcost;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Tag> ts(N);
        for(int i = 0; i < N; ++i) 
            cin >> ts[i].a >> ts[i].b >> ts[i].w;

        //edges[N] for start
        //edges[N+1] for goal
        vector<vector<pair<int, int> > > edges(N+2);
        for(int i = 0; i < N; ++i) {
            const Tag &ti = ts[i];
            for(int j = 0; j < N; ++j) {
                const Tag &tj = ts[j];
                if(ti.b >= tj.a) continue;
                edges[i].push_back(make_pair(j, tj.w));
            }
            edges[i].push_back(make_pair(N+1, 0));
            edges[N].push_back(make_pair(i, ti.w));
        }

        int ans = 0;
        vector<int> used(N+2, 0);
        for(int cnt = 0; cnt < 2; ++cnt) {
            vector<int> hist;
            best_cost = 0;
            ans += dfs(edges, N, 0, used, hist);
            for(int i = 0; i < best_hist.size(); ++i) {
                if(best_hist[i] < N) {
                    used[best_hist[i]] = 1;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
