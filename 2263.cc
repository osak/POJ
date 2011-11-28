//Name: Heavy Cargo
//Level: 2
//Category: 最短経路,ダイクストラ,グラフ,Dijkstra,Graph
//Note:

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct Tag {
    int cost, best, to;
    Tag() {}
    Tag(int c, int b, int t) : cost(c), best(b), to(t) {}
};

bool operator < (const Tag &t1, const Tag &t2) {
    return t1.cost < t2.cost;
}


map<string, int> name2idx;
vector<vector<pair<int, int> > > edges;
vector<bool> used(0, false);
vector<int> maxcost(0, 0);

int main() {
    for(int C = 1; ; ++C) {
        int curridx = 1;
        int n, r;
        string city1, city2;
        cin >> n >> r;
        if(n == 0 && r == 0) break;

        edges.clear();
        edges.resize(n+1);
        used.clear();
        used.resize(n+1);
        maxcost.clear();
        maxcost.resize(n+1);

        for(int i = 0; i < r; ++i) {
            int c1, c2, dist;
            cin >> city1 >> city2 >> dist;
            c1 = name2idx[city1];
            c2 = name2idx[city2];
            if(c1 == 0) c1 = name2idx[city1] = curridx++;
            if(c2 == 0) c2 = name2idx[city2] = curridx++;

            edges[c1].push_back(make_pair(dist, c2));
            edges[c2].push_back(make_pair(dist, c1));
        }

        cin >> city1 >> city2;
        int start = name2idx[city1];
        int goal = name2idx[city2];

        priority_queue<Tag> q;
        for(int i = 0; i < edges[start].size(); ++i) {
            q.push(Tag(edges[start][i].first, edges[start][i].first, edges[start][i].second));
        }
        used[start] = true;
        int minimum = INT_MAX;
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            if(used[t.to]) continue;
            used[t.to] = true;
            if(t.to == goal) {
                minimum = t.best;
                break;
            }

            for(int i = 0; i < edges[t.to].size(); ++i) {
                if(used[edges[t.to][i].second]) continue;
                q.push(Tag(edges[t.to][i].first, min(edges[t.to][i].first, t.best), edges[t.to][i].second));
            }
        }

        cout << "Scenario #" << C << endl;
        cout << minimum << " tons" << endl;
        cout << endl;
    }

    return 0;
}
