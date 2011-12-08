//Name: Colored stones
//Level: 3
//Category: 動的計画法,DP,bitDP
//Note:

/*
 * [石の位置][現在の色][今までに使った色(もう使用不可)]で取り除いた石の個数についてDP．
 * 使った色はbitで持つ．
 * DPの更新式は，
 * dp[pos][cur][flag] =   min(dp[pos-1][cur][flag], [ dp[pos-1][k][flag & (1<<k)] for k of (flag&(1<<k)) ])
 *                      + (v[pos] != cur)
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int dp[101][5][32]; //[pos][cur][flag]

int main() {
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<int> v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i];
            v[i]--;
        }

        for(int pos = 0; pos <= N; ++pos) {
            for(int cur = 0; cur < K; ++cur) {
                for(int flag = 0; flag < 1<<K; ++flag) {
                    dp[pos][cur][flag] = pos==0 ? 0 : N;
                }
            }
        }

        for(int pos = 1; pos <= N; ++pos) {
            for(int cur = 0; cur < K; ++cur) {
                for(int flag = 0; flag < 1<<K; ++flag) {
                    if(flag & (1<<cur)) continue;

                    dp[pos][cur][flag] = dp[pos-1][cur][flag];
                    for(int k = 0; k < K; ++k) {
                        if(flag & (1<<k)) dp[pos][cur][flag] = min(dp[pos][cur][flag], dp[pos-1][k][flag & ~(1<<k)]);
                    }
                    if(v[pos-1] != cur) {
                        dp[pos][cur][flag]++;
                    }
                    //cout << pos << ' ' << cur << ' ' << flag << ' ' << dp[pos][cur][flag] << endl;
                }
            }
        }

        int ans = N;
        for(int cur = 0; cur < K; ++cur) {
            for(int flag = 0; flag < 1<<K; ++flag) {
                ans = min(dp[N][cur][flag], ans);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
