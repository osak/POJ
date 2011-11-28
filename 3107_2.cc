//Name: Godfather
//Level: 2
//Category: グラフ,木,Graph
//Note: 隣接行列でPOJに投げるとTLEするので注意

/*
 * 木からあるノードを削除したとき，残る最大部分木の大きさは
 * ・そのノードの子のうち最大の部分木の大きさ
 * ・全体ノード数Nから自分と子のノードを引いた大きさ
 * のどちらかになる．
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Edge {
    int a, b;

    Edge() {}
    Edge(int a, int b) : a(a), b(b) {}

    bool operator < (const Edge &other) const {
        return a < other.a;
    }
};

typedef vector<Edge>::const_iterator Eit;

int dfs(int pos, vector<int> &maxrem, vector<int> &used, const vector<Edge> &edges, int N) {
    used[pos] = true;
    maxrem[pos] = 0;
    int sum = 0;
    pair<Eit,Eit> bound = equal_range(edges.begin(), edges.end(), Edge(pos, 0));

    for(Eit it = bound.first; it != bound.second; ++it) {
        if(used[it->b]) continue;
        int val = dfs(it->b, maxrem, used, edges, N);
        sum += val;
        maxrem[pos] = max(maxrem[pos], val);
    }
    maxrem[pos] = max(maxrem[pos], N-sum-1);
    
    return sum+1;
}

int main() {
    int N;
    scanf("%d", &N);

    vector<Edge> edges;
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges.push_back(Edge(a,b));
        edges.push_back(Edge(b,a));
    }
    sort(edges.begin(), edges.end());

    vector<int> maxrem(N+1, 0);
    vector<int> used(N+1, 0);
    int minval = N+1;
    dfs(1, maxrem, used, edges, N);
    for(int i = 1; i <= N; ++i)
        minval = min(minval, maxrem[i]);
    bool first = true;
    for(int i = 1; i <= N; ++i) {
        if(minval == maxrem[i]) {
            if(!first) printf(" ");
            printf("%d", i);
            first = false;
        }
    }
    puts("");

    return 0;
}
