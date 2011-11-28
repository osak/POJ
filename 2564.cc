#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int dist(const string &s1, const string &s2) {
    int dp[17][17];
    for(int i = 0; i <= s1.length(); ++i) dp[i][0] = i;
    for(int i = 0; i <= s2.length(); ++i) dp[0][i] = i;

    for(int i = 1; i <= s1.length(); ++i) {
        for(int j = 1; j <= s2.length(); ++j) {
            int cost = ((s1[i-1] == s2[j-1]) ? 0 : 1);
            dp[i][j] = min(min(dp[i-1][j] + 1, dp[i][j-1]+1), dp[i-1][j-1]+cost);
        }
    }

    return dp[s1.length()][s2.length()];
}

int seq[25000];

int main() {
    vector<string> dict;
    while(!cin.eof()) {
        string word;
        cin >> word;
        dict.push_back(word);
    }

    int maxlen = 0;
    for(int i = 0; i < dict.size(); ++i) {
        for(int j = i+1; j < dict.size(); ++j) {
            if(seq[j] < seq[i]+1) {
                if(dist(dict[i], dict[j]) <= 1) {
                    seq[j] = seq[i]+1;
                    if(seq[j] > maxlen) maxlen = seq[j];
                }
            }
        }
    }

    cout << maxlen+1 << endl;
    return 0;
}
