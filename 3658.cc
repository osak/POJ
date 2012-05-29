//Name: Artificial Lake
//Level: 4
//Category: シミュレーション,再帰
//Note:

/*
 * 問題の条件より，水が流れる点では両隣とも床より低くなっていることはありえない．
 * また，低い点に水を注いで埋めるのは，床が広くなるのと等価である．
 * これらのことから，ある点に水を注ぐとは
 * ・両隣が床よりも高ければ，低い方に到達するまで注ぎ続ける
 * ・どちらかが床よりも低ければ，床と同じ高さになるまで低いほうの点に水を注ぎ続ける
 *   このとき，低い方の点が同じ高さまで上がってくると，床が広くなる
 * ということであることが分かる．
 * 低い方に水を注ぐ操作は再帰的なので，方針としては
 * ・leftとrightをそれぞれ左と右の壁とする区間に，特定の高さまで水を注ぐ
 * ことを繰り返す関数を書けばよい．
 *
 * 愚直に再帰関数で実装したら，G++ではRE(スタックオーバーフロー)になった．
 * 仕方ないのでC++で投げて通した．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

typedef unsigned long long ULL;
const ULL INF = 10000000;
ULL t;
vector<ULL> ans;
vector<pair<int,int> > levels;

ULL fill_up(int pos, ULL width, ULL height, ULL target_height, int &left, int &right) {
    //cout << pos << ' ' << height << ' ' << left << ' ' << right << endl;
    while(true) {
        ULL left_h = levels[left].second;
        ULL right_h = levels[right].second;

        if(left_h > height && right_h > height) {
            ans[pos] = t + width;
            ULL th = min(left_h, right_h);
            t += width * (th-height);
            height = th;
        }
        else if(right_h < height) {
            int next = right;
            ++right;
            width += fill_up(next, levels[next].first, levels[next].second, height, pos, right);
        }
        else if(left_h < height) {
            int next = left;
            --left;
            width += fill_up(next, levels[next].first, levels[next].second, height, left, pos);
        }

        if(height == target_height) break;

        if(right_h == height) {
            int next = right;
            ++right;
            return fill_up(next, width+levels[next].first, height, target_height, left, right);
        }
        if(left_h == height) {
            int next = left;
            --left;
            return fill_up(next, width+levels[next].first, height, target_height, left, right);
        }
    }

    return width;
}

int main() {
    int N;
    scanf("%d", &N);
    levels.resize(N+2);
    ans.resize(N+2);
    int start = 1;
    int max_height = 0;
    for(int i = 1; i <= N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        levels[i] = make_pair(a, b);
        max_height = max(max_height, levels[i].second);
        if(levels[i].second < levels[start].second) {
            start = i;
        }
    }
    // sentinels
    levels[0] = make_pair(0, max_height+1);
    levels[N+1] = make_pair(0, max_height+1);

    t = 0;
    int left = start-1, right = start+1;
    fill_up(start, levels[start].first, levels[start].second, max_height+1, left, right);

    for(int i = 1; i <= N; ++i) {
        printf("%I64u\n", ans[i]);
    }

    return 0;
}
