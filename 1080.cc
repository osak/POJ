//Name: Human Gene Functions
//Level: 2
//Category: 動的計画法,最長共通部分列,DP,LCS
//Note: 

/*
 * LCSの変形問題。
 */
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <cstdio>

using namespace std;

const int table[][5] = {
    {5,-1,-2,-1,-3},
    {-1,5,-3,-2,-4},
    {-2,-3,5,-2,-2},
    {-1,-2,-2,5,-1},
    {-3,-4,-2,-1,0},
};

int cost(char c1, char c2) {
    const string s = "ACGT-";
    int idx1 = s.find(c1);
    int idx2 = s.find(c2);
    return table[idx1][idx2];
}

int main() {
    int N;
    cin >> N;
    while(N--) {
        int l;
        string s1, s2;

        cin >> l >> s1 >> l >> s2;
        
        vector<vector<int> > dp(s1.size()+1, vector<int>(s2.size()+1, INT_MIN/2));
        dp[0][0] = 0;
        for(int i = 1; i < s2.size()+1; ++i) dp[0][i] = dp[0][i-1] + cost('-', s2[i-1]);
        for(int i = 1; i < s1.size()+1; ++i) dp[i][0] = dp[i-1][0] + cost('-', s1[i-1]);

        for(int i1 = 1; i1 < s1.size()+1; ++i1) {
            for(int i2 = 1; i2 < s2.size()+1; ++i2) {
                char c1 = s1[i1-1], c2 = s2[i2-1];
                if(c1 == c2) dp[i1][i2] = dp[i1-1][i2-1] + cost(c1, c2);
                else dp[i1][i2] = max(dp[i1-1][i2-1] + cost(c1, c2), max(dp[i1-1][i2] + cost(c1, '-'), dp[i1][i2-1] + cost(c2, '-')));
            }
        }

        cout << dp[s1.size()][s2.size()] << endl;
    }
    return 0;
}
