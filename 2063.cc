//Name: Investment
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 毎年ごとに所持金から一番多くの収益が出るようDPすればよい．
 * そのままDPするとTLEだが，bondは全て1000の倍数の金額なので
 * 1000で割った数値でDPすれば間に合う．
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        int amount, P;
        cin >> amount >> P;

        int D;
        cin >> D;
        vector<pair<int, int> > bonds(D);
        for(int i = 0; i < D; ++i) 
            cin >> bonds[i].first >> bonds[i].second;

        for(int period = 0; period < P; ++period) {
            vector<int> dp(amount/1000+1, 0);
            for(int j = 0; j <= amount/1000; ++j) {
                for(int i = 0; i < D; ++i) {
                    const pair<int, int> b = bonds[i];
                    if(j-b.first/1000 >= 0) dp[j] = max(dp[j], dp[j-b.first/1000] + b.second);
                }
            }
            amount += dp[amount/1000];
        }
        cout << amount << endl;
    }
    return 0;
}
