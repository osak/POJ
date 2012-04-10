//Name: FDNY to the Rescue!
//Level: 2
//Category: グラフ,Graph,ダイクストラ法,Dijkstra,経路復元
//Note:

/*
 * 各スタート地点から目的地までの最短パスを求め，経路復元すればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 100000000;

struct Ans {
    int org, t;
    vector<int> path;

    Ans() {}
    Ans(int o, int t, vector<int> &p) : org(o), t(t), path(p) {}

    bool operator < (const Ans &other) const {
        return t < other.t;
    }
};

int main() {
    ios::sync_with_stdio(0);
    int N;
    cin >> N;

    vector<vector<int> > dist(N, vector<int>(N));
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N; ++c) {
            cin >> dist[r][c];
            if(dist[r][c] == -1) dist[r][c] = INF;
        }
    }

    int T;
    cin >> T;
    --T;

    vector<Ans> answers;
    {
        int start;
        while(cin >> start) {
            --start;
            vector<int> prev(N, -1);
            vector<int> dp(N, INF);
            priority_queue<pair<int,pair<int, int> > > q;
            q.push(make_pair(0, make_pair(start, -1)));
            while(!q.empty()) {
                int cost = -q.top().first;
                int pos = q.top().second.first;
                int prevpos = q.top().second.second;
                q.pop();

                if(dp[pos] < cost) continue;
                dp[pos] = cost;
                prev[pos] = prevpos;

                for(int i = 0; i < N; ++i) {
                    int nc = cost + dist[pos][i];
                    if(nc >= dp[i]) continue;
                    q.push(make_pair(-nc, make_pair(i, pos)));
                }
            }
            Ans ans;
            ans.t = dp[T];
            ans.org = start;

            int cur = T;
            while(cur != -1) {
                ans.path.push_back(cur);
                cur = prev[cur];
            }
            answers.push_back(ans);
        }
    }

    sort(answers.begin(), answers.end());

    cout << "Org\tDest\tTime\tPath" << endl;
    for(vector<Ans>::iterator it = answers.begin(); it != answers.end(); ++it) {
        cout << it->org+1 << "\t" << T+1 << "\t" << it->t;
        for(vector<int>::reverse_iterator it2 = it->path.rbegin(); it2 != it->path.rend(); ++it2) {
            cout << "\t" << *it2+1;
        }
        cout << endl;
    }

    return 0;
}
