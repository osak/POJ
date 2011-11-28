//Name: Code
//Level: 3
//Category: 文字列,順序付け
//Note:

#include <iostream>
#include <string>

using namespace std;

int dp[11][26];

int main() {
    for(int i = 0; i < 26; ++i) dp[0][i] = 0;
    for(int i = 0; i < 26; ++i) dp[1][i] = 1;
    for(int i = 2; i < 11; ++i) {
        for(int j = 0; j < 26; ++j) {
            dp[i][j] = 0;
            for(int k = j+1; k < 26; ++k) dp[i][j] += dp[i-1][k];
        }
    }

    string line;
    while(cin >> line) {
        bool ok = true;
        for(int i = 1; i < line.size(); ++i) {
            if(line[i-1] >= line[i]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            int code = 1;
            int N = line.size();
            char prev = 'a'-1;
            for(int i = 0; i < N; ++i) {
                for(int t = 0; t < 26; ++t)
                    code += dp[N-i-1][t];
                for(int t = prev-'a'+1; t < line[i]-'a'; ++t) code += dp[N-i][t];
                prev = line[i];
            }
            cout << code << endl;
        }
        else cout << 0 << endl;
    }

    return 0;
}
