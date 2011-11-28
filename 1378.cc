//Name: Power Cable Problem
//Level: 2
//Category: グラフ,Graph
//Note:

/*
 * それぞれのネットワークに浸水したビルが含まれていたら，その線をぜんぶ無効化する．
 * 最終的に一本も線が張られていないビルの数を答える．
 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int N, M, K;
        cin >> N >> M >> K;
        if(!N && !M && !K) continue;
        if(N == -1 && M == -1 && K == -1) break;

        vector<set<int> > net(M);
        vector<int> level(N, 0);
        for(int i = 0; i < M; ++i) {
            int ns;
            cin >> ns;
            for(int j = 0; j < ns; ++j) {
                int b;
                cin >> b;
                level[b]++;
                net[i].insert(b);
            }
        }
        vector<int> downed(M, 0);
        for(int k = 0; k < K; ++k) {
            int b;
            cin >> b;
            for(int m = 0; m < M; ++m) {
                if(!downed[m] && net[m].count(b)) {
                    for(set<int>::iterator it = net[m].begin(); it != net[m].end(); ++it) level[*it]--;
                    downed[m] = 1;
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < N; ++i) {
            if(level[i] == 0) ++ans;
        }

        cout << ans << endl;
    }
    return 0;
}
