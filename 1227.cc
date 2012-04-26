//Name: RoboContest
//Level: 2
//Category: 幅優先探索,BFS,偶奇,パリティ
//Note:

/*
 * ロボットがあるマスに行くのに要する手数のパリティだけを見ればよい．
 * （パリティが同じなら，隣りあったマスを往復することで手数は調整できる）
 * 全てのロボットが到達可能なマスとパリティが一つでもあればYES．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <bitset>

using namespace std;

struct Dict {
    int cnt;
    map<int,int> dict;

    Dict() : cnt(0) {}

    int get(int n) {
        if(dict.count(n)) return dict[n];
        return dict[n] = cnt++;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int N, K;
        cin >> N >> K;

        vector<vector<int> > v(N);
        vector<int> starts(K);
        Dict dict;
        for(int i = 0; i < N; ++i) {
            int id, ncnt;
            cin >> id >> ncnt;
            id = dict.get(id);
            while(ncnt--) {
                int neigh;
                cin >> neigh;
                v[id].push_back(dict.get(neigh));
            }
        }
        for(int i = 0; i < K; ++i) {
            int start;
            cin >> start;
            starts[i] = dict.get(start);
        }

        bitset<100> goals[2];
        for(int i = 0; i < N; ++i) {
            goals[0].set(i);
            goals[1].set(i);
        }
        for(vector<int>::iterator it = starts.begin(); it != starts.end(); ++it) {
            bitset<100> visited[2];
            bitset<100> candidates[2];

            queue<pair<int,int> > q;
            q.push(make_pair(*it, 0));
            while(!q.empty()) {
                int pos = q.front().first;
                int parity = q.front().second;
                q.pop();

                candidates[parity].set(pos);
                if(visited[parity].test(pos)) continue;
                visited[parity].set(pos);

                for(vector<int>::iterator it2 = v[pos].begin(); it2 != v[pos].end(); ++it2) {
                    int np = 1 - parity;
                    if(visited[parity].test(*it2)) continue;
                    visited[parity].set(*it2);
                    q.push(make_pair(*it2, np));
                }
            }
            goals[0] &= candidates[0];
            goals[1] &= candidates[1];
        }

        if(goals[0].count() > 0 || goals[1].count() > 0) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
