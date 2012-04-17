//Name: Widget Factory
//Level: 3
//Category: 方程式,有限体
//Note:

/*
 * mod 7の有限体で方程式を解く．
 * 7が素数なので，フェルマーの小定理よりnの逆元はpow(n,7-2)で求められることに注意．
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int& normalize(int &v) {
    while(v < 0) v += 7;
    if(v >= 7) v %= 7;
    return v;
}

int main() {
    map<string,int> daytbl;
    daytbl["MON"] = 0;
    daytbl["TUE"] = 1;
    daytbl["WED"] = 2;
    daytbl["THU"] = 3;
    daytbl["FRI"] = 4;
    daytbl["SAT"] = 5;
    daytbl["SUN"] = 6;

    vector<int> inv(8);
    for(int i = 1; i <= 7; ++i) {
        inv[i] = (int)pow(i, 7-2);
    }

    while(true) {
        int N, M;
        scanf("%d %d", &N, &M);
        if(!N && !M) break;

        vector<vector<int> > matrix(M, vector<int>(N+1));
        for(int i = 0; i < M; ++i) {
            int k;
            char start[4], end[4];
            scanf("%d %s %s", &k, start, end);
            matrix[i][N] = (daytbl[end]-daytbl[start]+1+7)%7;
            while(k--) {
                int t;
                scanf("%d", &t);
                matrix[i][t-1] += 1;
            }
        }
        for(int r = 0; r < M; ++r) {
            for(int c = 0; c < N+1; ++c) {
                normalize(matrix[r][c]);
            }
        }

        // for after check
        vector<vector<int> > orgmat = matrix;

        /*
        for(int r = 0; r < M; ++r) {
            for(int c = 0; c < N+1; ++c) {
                printf("%d ", matrix[r][c]);
            }
            puts("");
        }
        */

        vector<int> ansrow(N, -1);
        for(int r = 0; r < M; ++r) {
            int pivot = 0;
            while(pivot < N && (matrix[r][pivot] == 0 || ansrow[pivot] != -1)) ++pivot;
            if(pivot == N) continue;

            for(int rr = 0; rr < M; ++rr) {
                if(rr == r) continue;
                int a = matrix[rr][pivot] * inv[matrix[r][pivot]];
                normalize(a);
                for(int c = 0; c < N+1; ++c) {
                    matrix[rr][c] -= matrix[r][c]*a;
                    normalize(matrix[rr][c]);
                }
            }
            ansrow[pivot] = r;
        }
        
        vector<int> ans(N, 0);
        for(int t = 0; t < N; ++t) {
            int r = ansrow[t];
            if(r == -1) continue;
            ans[t] = matrix[r][N] * inv[matrix[r][t]];
            normalize(ans[t]);
            while(ans[t] < 3) ans[t] += 7;
            while(ans[t] > 9) ans[t] -= 7;
        }

        // Check consistency
        bool consistent = true;
        for(int r = 0; r < M; ++r) {
            int val = 0;
            for(int t = 0; t < N; ++t) {
                val += orgmat[r][t]*ans[t];
                normalize(val);
            }
            if(val != orgmat[r][N]) {
                consistent = false;
                break;
            }
        }

        // Check multiple
        bool multiple = (find(ansrow.begin(), ansrow.end(), -1) != ansrow.end());

        if(!consistent) {
            puts("Inconsistent data.");
        }
        else if(multiple) {
            puts("Multiple solutions.");
        }
        else {
            for(int t = 0; t < N; ++t) {
                if(t != 0) printf(" ");
                printf("%d", ans[t]);
            }
            puts("");
        }
    }

    return 0;
}
