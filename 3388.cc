//Name: Japanese Puzzle
//Level: 3
//Category: 二分探索,Special Judge
//Note: TLE厳しい

/*
 * 二分探索でn列が解になるかを確かめる．
 * 今回はよくある下限でなく上限を求める問題のため，(left, right]の区間で持って
 * center = (left+right+1)/2とすると良い．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    int N, K;
    scanf("%d %d", &N, &K);
    vector<int> v(K);
    for(int i = 0; i < K; ++i) scanf("%d", &v[i]);

    int left = 0, right = N;
    vector<int> ans;
    while(left < right) {
        int center = (left+right+1)/2;
        int cnt = 0;
        vector<int> list;
        for(int i = 0; i < K; ++i) {
            int n = v[i] / center;
            if(cnt+n >= N) n = N-cnt;
            for(int j = 0; j < n; ++j) {
                list.push_back(i+1);
            }
            cnt += n;
            if(cnt == N) break;
        }
        //cout << left << ' ' << right  << ' ' << cnt << endl;
        if(cnt == N) {
            left = center;
            ans.swap(list);
        }
        else right = center-1;
    }

    printf("%d\n", (left+right)/2);
    for(int i = 0; i < N; ++i) {
        printf("%d\n", ans[i]);
    }

    return 0;
}

