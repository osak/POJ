//Name: Treasure Hunters
//Level: 2
//Category: 探索
//Note:

/*
 * 宝の分配方法はH^T通りなので，全部試す．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int ipow(int a, int x) {
    int ret = 1;
    while(x--) ret *= a;
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string cmd;
    while(cin >> cmd) {
        int T, H;
        cin >> T >> H;
        vector<vector<int> > treasures(H, vector<int>(T));
        for(int i = 0; i < H; ++i) {
            for(int j = 0; j < T; ++j) {
                cin >> treasures[i][j];
            }
        }
        cin >> cmd; // ignore "END"

        unsigned lim = ipow(H, T);
        unsigned anspat = 0;
        int best = INT_MAX;
        vector<int> best_rewards;
        for(unsigned pat = 0; pat < lim; ++pat) {
            vector<int> rewards(H, 0);
            unsigned tmp = pat;
            for(int i = 0; i < T; ++i) {
                unsigned idx = tmp % H;
                rewards[idx] += treasures[idx][i];
                tmp /= H;
            }
            int diff = *max_element(rewards.begin(), rewards.end()) - *min_element(rewards.begin(), rewards.end());
            if(diff < best) {
                anspat = pat;
                best = diff;
                best_rewards = rewards;
            }
        }

        vector<vector<int> > v(H);
        for(int i = 0; i < T; ++i) {
            unsigned idx = anspat % H;
            v[idx].push_back(i+1);
            anspat /= H;
        }
        for(int i = 0; i < H; ++i) {
            for(vector<int>::iterator it = v[i].begin(); it != v[i].end(); ++it) {
                cout << *it << ' ';
            }
            cout << best_rewards[i] << endl;
        }
        cout << endl;
    }

    return 0;
}
