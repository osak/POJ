#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//台数, 片側の搭載長さ
int dp[300][10001];

int main() {
    int flen;
    cin >> flen;
    flen *= 100;

    int idx = 0;
    int sum = 0;
    int bestidx = 0;
    int bestlen = 0;
    vector<int> lens;

    dp[0][0] = -1;
    while(true) {
        int len;
        cin >> len;
        if(len == 0) break;
        lens.push_back(len);

        for(int i = 0; i <= flen; ++i) {
            if(dp[idx][i] != 0) {
                //こっちに搭載
                if(i + len <= flen) {
                    dp[idx+1][i + len] = 1;
                    bestidx = idx+1;
                    bestlen = i+len;
                }

                //向こうに搭載
                if(sum - i + len <= flen) {
                    dp[idx+1][i] = 2;
                    bestidx = idx+1;
                    bestlen = i;
                }
            }
        }
        sum += len;
        if(++idx > 300-1) break;
    }

    stack<string> s;
    int currlen = bestlen;
    for(int i = bestidx; i > 0; --i) {
        if(dp[i][currlen] == 1) {
            s.push("starboard");
            currlen -= lens[i-1];
        }
        else {
            s.push("port");
        }
    }
    cout << bestidx << endl;
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}
