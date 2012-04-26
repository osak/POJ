// Name: Naptime
// Level: 4
// Category: 動的計画法,DP
// Note: 問題文が微妙

/*
 * 問題文が曖昧だが，何周もしてUtilityを稼ぐ問題ではなく，一周分の生活リズムを決めて
 * その生活リズムで得られるUtilityを最大化する問題である．
 * 一周で終わるので，当然睡眠時間は使い切るに越したことはない．
 *
 * ある時刻に起きているか寝ているかの状態は
 * ・起きている
 * ・寝始めた最初
 * ・寝ている
 * の3状態を取る．
 * ループを考慮しない場合，[時間][残り睡眠時間][状態]でDPする．
 * （到達不可能な状態変数の組み合わせがあり，これは無視しないといけないことに注意）
 *
 * ループを考えることは結局時間0のUtilityを組み入れるかどうかという問題になるが，
 * 時間0を組み入れるためには遅くとも時間Nで寝始めていないといけない．
 * よって，時間0を組み入れない時と組み入れる時の2回に分けて同じDPを行い，
 * 時間Nにおいて前者は全状態，後者は「起きている」以外の状態からmaxを取ればよい．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>

using namespace std;

// dp[bufidx][remain][state]
// state:
//  0: awaken
//  1: head period in bed
//  2: tail period in bed
int dp[2][3831][3];
int N, B;

inline int get(int idx, int r, int s) {
    if(r > B) return INT_MIN;
    return dp[idx][r][s];
}

inline void set(int idx, int r, int s, int v) {
    if(v < 0) v = INT_MIN;
    dp[idx][r][s] = v;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> B;

    vector<int> nap(N);
    for(int i = 0; i < N; ++i) {
        cin >> nap[i];
    }

    
    int ans = -1;
    // Not Count first period
    int idx = 0;
    for(int i = 0; i <= B; ++i) {
        for(int j = 0; j < 3; ++j) {
            set(idx, i, j, -1);
        }
    }
    set(idx, B, 0, 0);
    set(idx, B-1, 1, 0);
    for(int pos = 1; pos < N; ++pos) {
        for(int rem = 0; rem <= B; ++rem) {
            set(1-idx, rem, 0, max(get(idx, rem, 0), max(get(idx, rem, 1), get(idx, rem, 2))));
            set(1-idx, rem, 1, get(idx, rem+1, 0));
            set(1-idx, rem, 2, max(get(idx, rem+1, 1), get(idx, rem+1, 2)) + nap[pos]);
        }
        idx = 1-idx;
    }
    ans = max(get(idx, 0, 0), max(get(idx, 0, 1), get(idx, 0, 2)));

    // Count first period
    idx = 0;
    for(int i = 0; i <= B; ++i) {
        for(int j = 0; j < 3; ++j) {
            set(idx, i, j, -1);
        }
    }
    set(idx, B-1, 2, nap[0]);
    for(int pos = 1; pos < N; ++pos) {
        for(int rem = 0; rem <= B; ++rem) {
            set(1-idx, rem, 0, max(get(idx, rem, 0), max(get(idx, rem, 1), get(idx, rem, 2))));
            set(1-idx, rem, 1, get(idx, rem+1, 0));
            set(1-idx, rem, 2, max(get(idx, rem+1, 1), get(idx, rem+1, 2)) + nap[pos]);
        }
        idx = 1-idx;
    }
    ans = max(ans, max(get(idx, 0, 1), get(idx, 0, 2)));

    cout << ans << endl;
    return 0;
}
