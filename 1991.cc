//Name: Turning in Homework
//Level: 4
//Category: DP
//Note:

/*
 * バス停でゴールする直前の状態を考えると，ある座標xにいて
 * 「xからバス停までに移動する間の点全てで宿題を提出でき，これで全部埋まる」
 * (実際にここで提出するか，あらかじめ提出しているかは関係ない)
 * →「xについてバス停と反対側の点は，すべて埋まっている」
 * という状態になっているはずである．
 * さらにこの一手前を考えると，座標yにいて
 * 「yからxまでに移動する間の点全てで宿題を提出でき，戻る必要なく埋まる．ただしxとバス停の間の点は考えない」
 * →「yについてxと反対側の点は，すべて埋まっている」
 * となる．
 *
 * これを繰り返すと，結局
 * 「ある点lより左側の点は全て埋まっている & ある点rより右側の点は全て埋まっている」
 * という状態を作るのにかかる時間が問題となることがわかる．
 * つまり，逆に考えて
 * 「区間(l,r)以外の点は埋まっている」
 * という情報と，左右どちらの境界にいるかでDPすればよい．
 * DPの更新式は，区間を1つずつ狭めていくことを考えれば出る．
 *
 * 廊下は隅から隅まで訪問する必要はないことに注意．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 20000;

int H, B;
int LLIM, RLIM;

// [left][right][on_left]
int dp[1002][1002][2];
int& dpref(int left, int right, int on_left) {
    return dp[left+1][right+1][on_left];
}

int solve(const vector<int> &ts, int left, int right, int on_left) {
    if(left > right) return INF;
    if(left < LLIM-1 || right > RLIM+1) return INF;

    int &res = dpref(left, right, on_left);
    if(res < INF) return res;

    int target = on_left ? left : right;
    int from_left = on_left ? 
        solve(ts, left-1, right, 1) + abs(target-(left-1)) :
        solve(ts, left, right+1, 1) + abs(target-left);
    if(from_left < ts[target]) from_left = ts[target];

    int from_right = on_left ?
        solve(ts, left-1, right, 0) + abs(target-right) :
        solve(ts, left, right+1, 0) + abs(target-(right+1));
    if(from_right < ts[target]) from_right = ts[target];
    //cout << left << ' ' << right << ' ' << on_left << ' ' << from_left <<  ' ' << from_right << endl;

    return res = min(from_left, from_right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int C;
    cin >> C >> H >> B;

    LLIM = RLIM = B;
    vector<int> ts(H+1, 0);
    for(int i = 0; i < C; ++i) {
        int h, t;
        cin >> h >> t;
        ts[h] = max(ts[h], t);
        LLIM = min(LLIM, h);
        RLIM = max(RLIM, h);
    }

    for(int i = 0; i < 1002; ++i) {
        for(int j = 0; j < 1002; ++j) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    dpref(LLIM, RLIM+1, 1) = max(LLIM, ts[LLIM]);
    dpref(LLIM-1, RLIM, 0) = max(RLIM, ts[RLIM]);

    cout << min(solve(ts, B, B, 1), solve(ts, B, B, 0)) << endl;
    return 0;
}
