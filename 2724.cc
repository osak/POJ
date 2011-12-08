//Name: Purifying Machine
//Level: 3
//Category: 二部マッチング
//Note:

/*
 * *が高々一つなので，一度に処理できる組について二部マッチングすればよい．
 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

//・左からフローが流れてくるため、右から左へ行くのは既に存在しているフローの逆流のみ
//・よって、右から左へ行って、そこでtrueで止まることはあり得ない
//　（左頂点は右へのmatchToがあり、かつそちらへは進めないので必ずfalseになる）
//・このアルゴリズムでは、
//　n：左頂点
//　g[n][i]：右頂点
//　matchTo[g[n][i]]：左頂点or-1
//　が成立している
//Verified AOJ 1163
bool bm_helper(const vector<vector<int> > &g, vector<int> &matchTo, int n, vector<bool> &used) {
    if(n == -1) return true;

    for(int i = 0; i < g[n].size(); ++i) {
        if(used[g[n][i]]) continue;
        //どうせこの頂点に戻ってきてもaugment pathは見つかるわけないので復元しなくてよい
        used[g[n][i]] = true;
        if(bm_helper(g, matchTo, matchTo[g[n][i]], used)) {
            //matchTo[n] = g[n][i];
            matchTo[g[n][i]] = n;
            return true;
        }
    }
    return false;
}

//gは接続配列（湧きだし、吸い込みはいらない）
//Lはマッチングの左側頂点の境界（L未満が左側）
//Verified AOJ 1163
int bipartiteMatch(const vector<vector<int> > &g, int L) {
    int size = g.size();
    vector<int> match(size, -1);
    //深さ優先でaugment pathを見つける
    //Ford Furlkersonのアルゴリズム。
    //一回の走査で必ずフローが1は増えるため、
    //左側を全てなめ尽くしたあとは解になっている
    int cnt = 0;
    for(int i = 0; i < L; ++i) {
        //if(__builtin_popcount(i) % 2 == 0) continue;
        vector<bool> used(g.size(), false);
        if(bm_helper(g, match, i, used)) ++cnt; //augment pathが見つかる->フローが1増える
    }
    return cnt/2;
    cnt = 0;
    for(int i = 0; i < size; ++i) {
        if(match[i] != -1 && match[match[i]] == i) cnt++;
    }
    return cnt/2;
}


int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<int> v(1<<N, 0);
        int infected = 0;
        for(int i = 0; i < M; ++i) {
            string s;
            cin >> s;

            int star = -1;
            int n = 0;
            for(int j = 0; j < s.size(); ++j) {
                if(s[j] == '*') {
                    star = j;
                }
                else n |= (s[j]-'0') << j;
            }
            if(!v[n]) ++infected;
            v[n] = 1;
            if(star != -1) {
                int idx = n|(1<<star);
                if(!v[idx]) infected++;
                v[idx] = 1;
            }
        }

        vector<vector<int> > graph(1<<N);
        for(int i = 0; i < (1<<N); ++i) {
            if(!v[i]) continue;
            for(int j = 0; j < (1<<N); ++j) {
                if(!v[j]) continue;
                int mask = i ^ j;
                if(__builtin_popcount(mask) == 1) {
                    graph[i].push_back(j);
                }
            }
        }
        
        int cnt = bipartiteMatch(graph, 1<<N);
        cout << infected - cnt << endl;
    }
    return 0;
}
