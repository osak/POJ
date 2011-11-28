//Name: The mysterious X network
//Level: 1
//Category: グラフ, 幅優先探索,やるだけ,BFS
//Note:

/*
 * 最短ルートを見つければよいので幅優先探索やるだけ。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int> > v(N);
    for(int i = 0; i < N; ++i) {
        int label, n;
        cin >> label >> n;
        while(n--) {
            int t;
            cin >> t;
            v[label].push_back(t);
        }
    }

    int c1, c2;
    cin >> c1 >> c2;

    vector<int> used(N, 0);
    queue<pair<int, int> > q;
    q.push(make_pair(c1, 0));
    int ans = 0;
    while(!q.empty()) {
        int n = q.front().first;
        int cost = q.front().second;
        q.pop();

        if(n == c2) {
            ans = cost-1;
            break;
        }

        for(int i = 0; i < v[n].size(); ++i) {
            if(!used[v[n][i]]) {
                q.push(make_pair(v[n][i], cost+1));
                used[v[n][i]] = 1;
            }
        }
    }
    cout << c1 << ' ' << c2 << ' ' << ans << endl;
    return 0;
}
