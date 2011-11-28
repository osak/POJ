//Name: Find The Multiple
//Level: 2
//Category: 数論,DP
//Note:

/*
 * 下からi桁目に1を立てると、mod mを取った値が10**i % mだけ増加する。
 * mod mで0になる値を見つければよいが、周期性があるのでDPする。
 */
#include <iostream>
#include <string>
#include <cstring>
#include <stack>

using namespace std;

int dp[200][200];

int main() {
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        if(n == 1) {
            cout << 1 << endl; 
            continue;
        }
        memset(dp, 0, sizeof(int)*200*200);

        int mod = 1;
        stack<int> modstack;
        modstack.push(1);
        dp[0][0] = -1;
        for(int i = 1; i < 200; ++i) {
            for(int j = 0; j < n; ++j) {
                if(dp[i-1][j] != 0) {
                    int next = (j + mod) % n;
                    dp[i][j] = -1;
                    dp[i][next] = 1;
                    if(next == 0) {
                        mod = next;
                        for(int k = i; k >= 1; --k) {
                            cout << ((dp[k][mod]==1) ? 1: 0);
                            if(dp[k][mod] == 1) {
                                mod = (mod - modstack.top() + n) % n;
                            }
                            modstack.pop();
                        }
                        cout << endl;
                        goto endloop;
                    }
                }
            }
            mod = (mod*10) % n;
            modstack.push(mod);
        }
endloop:
        ;
    }
}
