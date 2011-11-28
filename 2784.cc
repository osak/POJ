//Name: Buy or Build
//Level: 3
//Category: 最小全域木,MST,全探索
//Note:

/*
 * Subnetworkの選び方を全部試しながら、Kruskal法で最小全域木を求める。
 * ・Subnetworkの選び方が最大2**8 = 256
 * ・Kruskal法のオーダーがO(ElogV) = 最大1000**2*log(1000)
 * 二つをかけるとだいたい25億ループくらいとなって微妙な感じだが、
 * 処理の内容がたいしたことないせいか普通に通るっぽい。
 * （参考までに、このコードは969MSで通った）
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

//Verified PKU 2524
int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}

struct Tag {
    int c1, c2;
    int cost;

    Tag() {}
    Tag(int c1, int c2, int cs) : c1(c1), c2(c2), cost(cs) {}

    bool operator < (const Tag &other) const {
        return cost < other.cost;
    }
};

int dist(pair<int, int> c1, pair<int, int> c2) {
    return (c1.first-c2.first)*(c1.first-c2.first) + (c1.second-c2.second)*(c1.second-c2.second);
}

int main() {
    ios::sync_with_stdio(0);

    int N, Q;
    cin >> N >> Q;
    vector<vector<int> > sn(Q);
    vector<int> cost_sn(Q);
    vector<pair<int, int> > city(N);
    vector<Tag> dists;
    for(int i = 0; i < Q; ++i) {
        int n;
        cin >> n >> cost_sn[i];
        while(n--) {
            int v;
            cin >> v;
            v--;
            sn[i].push_back(v);
        }
    }

    for(int i = 0; i < N; ++i) 
        cin >> city[i].first >> city[i].second;

    for(int i = 0; i < N; ++i)
        for(int j = i+1; j < N; ++j)
            dists.push_back(Tag(i, j, dist(city[i], city[j])));

    sort(dists.begin(), dists.end());
    int ans = INT_MAX;
    for(int mask = 0; mask < (1<<Q); ++mask) {
        int cost = 0;
        vector<int> roots(N);
        vector<int> levels(N, 0);
        for(int i = 0; i < N; ++i) roots[i] = i;
        for(int i = 0; i < Q; ++i) {
            if(mask & (1<<i)) {
                for(int j = 0; j < sn[i].size(); ++j) unite(sn[i][0], sn[i][j], roots, levels);
                cost += cost_sn[i];
            }
        }

        for(int i = 0; i < dists.size(); ++i) {
            const Tag &t = dists[i];
            if(getroot(t.c1, roots) == getroot(t.c2, roots)) continue;
            cost += t.cost;
            unite(t.c1, t.c2, roots, levels);
        }
        ans = min(ans, cost);
    }
    cout << ans << endl;
}
