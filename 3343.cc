//Name: Against Mammoths
//Level: 3
//Category: 二部マッチング,最大流,Maximum Flow,二分探索,Binary Search
//Note:

/*
 * N年経過したときに攻め込んだとき勝てるかは二部マッチングで分かる．
 * あとはNに対して二分探索すればよい．
 * N年地点で一度に攻め込むのではなく，N年までの任意の点でばらばらに攻めてよいことに注意．
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct Planet {
    int init;
    int rate;

    Planet() {}
    Planet(int i, int r) : init(i), rate(r) {}
};

//・左からフローが流れてくるため、右から左へ行くのは既に存在しているフローの逆流のみ
//・よって、右から左へ行って、そこでtrueで止まることはあり得ない
//　（左頂点は右へのmatchToがあり、かつそちらへは進めないので必ずfalseになる）
//・このアルゴリズムでは、
//　n：左頂点
//　g[n][i]：右頂点
//　matchTo[g[n][i]]：左頂点or-1
//　が成立している
//Verified AOJ 1163
//Verified POJ 3343
bool bm_helper(const vector<vector<int> > &g, vector<int> &matchTo, int n, vector<int> &used) {
    if(n == -1) return true;

    for(vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if(used[*it]) continue;
        //どうせこの頂点に戻ってきてもaugment pathは見つかるわけないので復元しなくてよい
        used[*it] = true;
        if(bm_helper(g, matchTo, matchTo[*it], used)) {
            matchTo[n] = *it;
            matchTo[*it] = n;
            return true;
        }
    }
    return false;
}

//gは接続配列（湧きだし、吸い込みはいらない）
//Lはマッチングの左側頂点の境界（L未満が左側）
//Verified AOJ 1163
//Verified POJ 3343
int bipartiteMatch(const vector<vector<int> > &g, int L) {
    int size = g.size();
    vector<int> match(size, -1);
    //深さ優先でaugment pathを見つける
    //Ford Furlkersonのアルゴリズム。
    //一回の走査で必ずフローが1は増えるため、
    //左側を全てなめ尽くしたあとは解になっている
    int cnt = 0;
    for(int i = 0; i < L; ++i) {
        vector<int> used(g.size(), false);
        if(bm_helper(g, match, i, used)) ++cnt; //augment pathが見つかる->フローが1増える
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);

    while(true) {
        int H, A;
        cin >> H >> A;
        if(!H && !A) break;

        vector<Planet> human(H);
        vector<Planet> alien(A);
        vector<vector<int> > dist(H, vector<int>(A));

        for(int i = 0; i < H; ++i) {
            cin >> human[i].init >> human[i].rate;
        }
        for(int i = 0; i < A; ++i) {
            cin >> alien[i].init >> alien[i].rate;
        }
        for(int i = 0; i < H; ++i) {
            for(int j = 0; j < A; ++j) {
                cin >> dist[i][j];
            }
        }

        int left = 0, right = 2000000;
        while(left < right) {
            int center = (left+right)/2;
            vector<vector<int> > graph(H+A);
            for(int i = 0; i < H; ++i) {
                for(int j = 0; j < A; ++j) {
                    long long h = human[i].init + (long long)human[i].rate*(center-dist[i][j]);
                    long long a = alien[j].init + (long long)alien[j].rate*center;
                    if(center < dist[i][j]) h = -1;
                    if(human[i].init >= alien[j].init+(long long)alien[j].rate*dist[i][j] || h >= a) {
                        graph[i].push_back(H+j);
                    }
                }
            }
            if(bipartiteMatch(graph, H) == A) {
                right = center;
            }
            else {
                left = center+1;
            }
        }
        int ans = (left+right)/2;
        if(ans == 2000000) cout << "IMPOSSIBLE" << endl;
        else cout << (left+right)/2 << endl;
    }

    return 0;
}
