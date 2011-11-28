//Name: Exchange Rates
//Level: 2
//Category: 動的計画法,DP
//Note: 最初に持っているのはCanadian dollarであることに注意

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<double> rate(N);
        for(int i = 0; i < N; ++i) cin >> rate[i];

        //0 for US dollar, 1 for Canadian dollar
        vector<vector<int> > dp(2, vector<int>(N+1, 0));
        dp[1][0] = 1000*100;

        for(int i = 1; i <= N; ++i) {
            double r = rate[i-1];
            double invr = 1.0 / rate[i-1];
            for(int j = 0; j < i; ++j) {
                dp[0][i] = max(dp[0][i], max(dp[0][j], (int)(dp[1][j]*0.97*(invr))));
                dp[1][i] = max(dp[1][i], max(dp[1][j], (int)(dp[0][j]*0.97*(r))));
            }
        }

        printf("%d.%02d\n", dp[1][N]/100, dp[1][N]%100);
    }
    return 0;
}
