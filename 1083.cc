//Name: Moving Tables
//Level: 2
//Category: Greedy,貪欲法
//Note:

/*
 * 区間が消えようが消えるまいが，使える区間の数は変わらない．
 * (残っている区間の組は選び方の制約にならない)
 * また，互いに干渉する区間の選び方がn通りあるときは，どうせn手かかる．
 * したがって，重なっていない範囲を一度にできる限り多く処理すればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<pair<int,int> > v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i].first >> v[i].second;
            v[i].first = (v[i].first-1) / 2;
            v[i].second = (v[i].second-1) / 2;
            if(v[i].first > v[i].second) swap(v[i].first, v[i].second);
        }
        sort(v.begin(), v.end());

        vector<bool> used(N, false);
        int cnt = 0;
        int usecnt = 0;
        while(true) {
            int right = -1;
            for(int i = 0; i < N; ++i) {
                if(used[i]) continue;
                if(v[i].first > right) {
                    used[i] = true;
                    ++usecnt;
                    right = v[i].second;
                }
            }
            ++cnt;
            if(usecnt == N) break;
        }

        cout << cnt*10 << endl;
    }

    return 0;
}
