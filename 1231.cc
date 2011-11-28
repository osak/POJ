//Name: The Alphabet Game
//Level: 3
//Category: 実装
//Note:

/*
 * 分割線は各アルファベットについて囲み切る矩形の辺だけを考えればよい．
 * あとはひたすらこれらの辺で全体を分割し，最後に条件を満たしていれば勝利．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

typedef pair<int,int> Range;

struct Tag {
    int letter;
    Range h, v;

    Tag() {}
    Tag(int l, const Range &h, const Range &v) : letter(l), h(h), v(v) {}
};

bool inRange(int a, int x, int b) {
    return a < x && x < b;
}

vector<vector<int> > regroup(const vector<Tag> &ts, vector<vector<int> > &groups, int bound, bool horiz) {
    vector<vector<int> > new_groups;

    for(int i = 0; i < ts.size(); ++i) {
        const Range &r = horiz ? ts[i].h : ts[i].v;
        if(inRange(r.first, bound, r.second)) return groups;
    }

    for(int i = 0; i < groups.size(); ++i) {
        const vector<int> &v = groups[i];
        vector<int> left, right;
        for(int j = 0; j < v.size(); ++j) {
            const Tag &t = ts[v[j]];
            const Range &r = horiz ? t.h : t.v;
            if(r.second <= bound) right.push_back(v[j]);
            else left.push_back(v[j]);
        }
        if(!left.empty()) new_groups.push_back(left);
        if(!right.empty()) new_groups.push_back(right);
    }
    return new_groups;
}

int main() {
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int K, P;
        cin >> K >> P;

        vector<Tag> ts;
        for(int i = 0; i < K; ++i) {
            int l, r, t, b;
            l = t = INT_MAX;
            r = b = INT_MIN;
            for(int j = 0; j < P; ++j) {
                int x, y;
                cin >> x >> y;
                l = min(l, x-1); r = max(r, x);
                t = min(t, y-1); b = max(b, y);
            }
            ts.push_back(Tag(i, Range(l, r), Range(t, b)));
        }

        vector<vector<int> > groups(1);
        for(int i = 0; i < ts.size(); ++i) groups[0].push_back(i);

        for(int i = 0; i < ts.size(); ++i) {
            groups = regroup(ts, groups, ts[i].h.first, true);
            groups = regroup(ts, groups, ts[i].h.second, true);
            groups = regroup(ts, groups, ts[i].v.first, false);
            groups = regroup(ts, groups, ts[i].v.second, false);
        }
        cout << ((groups.size() == K) ? "YES" : "NO") << endl;
    }
    return 0;
}
