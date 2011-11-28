#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int N, L;
    cin >> N >> L;

    vector<int> cows(N);
    for(int i = 0; i < N; ++i) {
        cin >> cows[i];
    }

    int sl = (L+1-N)/(N-1);
    int lcnt = (L+1-N)%(N-1);

    vector<vector<int> > dp(2, vector<int>(N, INT_MAX/2));
    int ptr = 0;
    
    dp[ptr][0] = cows[0];
    for(int i = 1; i < N; ++i) {
        for(int j = 0; j <= min(i, lcnt); ++j) {
            int pos = (sl+1)*j + sl*(i-j) + i;
            int d = abs(cows[i]-pos);
            if(j > 0) dp[1-ptr][j] = min(dp[ptr][j-1] + d, dp[ptr][j] + d);
            else dp[1-ptr][j] = dp[ptr][j] + d;
        }
        ptr = 1-ptr;
    }
    cout << dp[ptr][lcnt] << endl;
    return 0;
}
