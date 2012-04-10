//Name: Covering
//Level: 2
//Category: DP
//Note:

/*
 * 探査エリアは整数座標にしか置けないので，地雷の場所は整数に丸めてしまってよい．
 * あとは区画ごとに累積和を求めて最大の箇所を出力する．
 * upper-most, right-most（x, y座標ともに最大）のものを出力することに注意．
#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

int cnt[1000][1000];
int dp[1000][1000];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int K, N, M;
        scanf("%d %d %d", &K, &N, &M);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < K; ++i) {
            double r, c;
            scanf("%lf %lf", &c, &r);
            if(r < N && c < N) cnt[(int)r][(int)c]++;
        }

        /*
        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < N; ++c) {
                printf("%3d", cnt[r][c]);
            }
            puts("");
        }
        puts("");
        */

        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < N; ++c) {
                int top = r > 0 ? dp[r-1][c] : 0;
                int left = c > 0 ? dp[r][c-1] : 0;
                int prev = (r > 0 && c > 0) ? dp[r-1][c-1] : 0;
                dp[r][c] = top + left + cnt[r][c] - prev;
                //printf("%3d", dp[r][c]);
            }
            //puts("");
        }

        pair<int,int> ans;
        int best = 0;
        for(int r = M-1; r < N; ++r) {
            for(int c = M-1; c < N; ++c) {
                int top = r-M >= 0 ? dp[r-M][c] : 0;
                int left = c-M >= 0 ? dp[r][c-M] : 0;
                int prev = (r-M >= 0 && c-M >= 0) ? dp[r-M][c-M] : 0;
                int cnt = dp[r][c] - top - left + prev;
                if(cnt >= best) {
                    ans = make_pair(r-M+1, c-M+1);
                    best = cnt;
                }
            }
        }

        printf("%d %d\n", ans.second, ans.first);
    }

    return 0;
}
