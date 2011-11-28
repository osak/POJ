#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    int N, R;
    cin >> N >> R;

    vector<int> nap(N);
    for(int i = 0; i < N; ++i) {
        cin >> nap[i];
    }

    //v[i][j] = utility when sleeping j periods from i 
    vector<vector<int> > v(N);
    for(int i = 0; i < N; ++i) {
        v[i].push_back(0);
        int sum = 0;
        for(int len = 1; len+i < N; ++len) {
            v[i].push_back(sum);
            sum += nap[i+len];
        }
    }

    //dp[last_wake][used]
    int ans = 0;
    vector<vector<int> > dp(N, vector<int>(R+1, 0));
    for(int i = 0; i < N; ++i) { //last_wake
        for(int r = 0; r <= R; ++r) { //used
            for(int j = 0; j < v[i].size(); ++j) { //to_sleep_len
                if(r+j > R) break;
                if(i+j >= N) break;
                dp[i+j][r+j] = max(dp[i+j][r+j], dp[i][r] + v[i][j]);
                ans = max(ans, dp[i+j][r+j]);
            }
        }
    }
    
    //0に後ろから接続するとき
    /*
    for(int i = 0; i < N; ++i)
        for(int r = 0; r < R+1; ++r)
            dp[i][r] = 0;
    for(int i = 0; i < N; ++i) {
        for(int r = 0; r <= R; ++r) {
            if(i == 0 && r != 1) continue;
            for(int j = 0; j < v[i].size(); ++j) {
                if(r+j > R) break;
                if(i+j >= N) break;
                int val = v[i][j];
                if(i == 0) val += nap[0];
                dp[i+j][r+j] = max(dp[i+j][r+j], dp[i][r] + val);
            }
        }
    }
    */
    for(int i = 1; i < N; ++i) {
        int len = N - i;
        int r = R - len;
        if(len >= 0 && r >= 0) {
            ans = max(ans, dp[i-1][r] + v[i][len] + nap[0]);
            cout << i << ' ' << len << ' ' << r << ' ' << ans << endl;
        }
    }

    cout << ans << endl;
    return 0;
}
