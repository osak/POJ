//Name: Cow Cycling
//Level: 3
//Category: グラフ,ダイクストラ,Graph,Dijkstra
//Note:

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Tag {
    int t, n, e, d;

    Tag(int t, int n, int e, int d) : t(t), n(n), e(e), d(d) {}

    bool operator < (const Tag &other) const {
        return t > other.t;
    }
};

int memo[21][101][101];

int main() {
    int N, E, D;
    cin >> N >> E >> D;

    int ans = 0;
    priority_queue<Tag> q;
    q.push(Tag(0, N, E, 0));
    while(!q.empty()) {
        const Tag t = q.top();
        q.pop();
        if(t.d >= D) {
            ans = t.t;
            break;
        }
        if(memo[t.n][t.e][t.d]) continue;

        memo[t.n][t.e][t.d] = 1;

        for(int i = 0; i <= 10; ++i) {
            if(t.e < i*i) break;
            if(memo[t.n][t.e-i*i][t.d+i]) continue;
            q.push(Tag(t.t+1, t.n, t.e-i*i, t.d+i));
        }
        if(t.n >= 2) {
            int e = E - t.d;
            for(int i = 0; i <= 10; ++i) {
                if(e < i*i) break;
                if(memo[t.n-1][e-i*i][t.d+i]) continue;
                q.push(Tag(t.t+1, t.n-1, e-i*i, t.d+i));
            }
        }
    }

    cout << ans << endl;
    return 0;
}
