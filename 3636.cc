//Name: Nested Dolls
//Level: 4
//Category: DAG,最小パス被覆,Minimum path cover
//Note:

/*
 * 入れ子にできる関係はDAGになるので，最小パス被覆を求めればよい．
 * ただし二部マッチングだとTLEしてしまうので工夫が必要になる．
 *
 * ここでは，素性が数値なので簡単にトポロジカルソートできることに注目する．
 * 具体的には，pair<int,int>でソートすればトポロジカルソートになる．
 * これを先頭からたどって行き，それぞれのパスの先端だけを覚えておいて
 * つなげられる頂点を訪問したときに先端を更新すればよい．
 *
 * 先端を更新するとき，複数のパスがひとつの頂点で合流することがある．
 * このときは接続可能な先端のうち，なるべくsecondが大きいものと接続する．
 * （接続されなかったパスは孤立して被覆パス数を増やす要因となるが，secondが小さければ
 *   あとで他のパスと併合できる可能性があるため．
 *   頂点のソートのしかたから，訪問する頂点のfirstは広義単調増加であることに注意．）
 * 
 * これらの操作を高速に行うため，firstの単調性に注目してsecondのみを保持したmultisetで
 * パスの先端を管理する．
 * このとき，愚直に先頭から処理していくと等しいfirstを持つ頂点間で干渉するため，
 * 同じfirstの間では更新処理（古い先端の削除，新しい先端の挿入）のうち，先端の削除を先にまとめて
 * 行う必要がある．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    //cin >> N;
    scanf("%d", &N);
    while(N--) {
        int M;
        //cin >> M;
        scanf("%d", &M);
        vector<pair<int,int> > dolls(M);
        for(int i = 0; i < M; ++i) {
            int w, h;
            scanf("%d %d", &w, &h);
            dolls[i] = make_pair(w, h);
            //cin >> dolls[i].first >> dolls[i].second;
        }
        sort(dolls.begin(), dolls.end());

        multiset<int> cur;
        vector<pair<int,int> >::iterator it = dolls.begin();
        while(it != dolls.end()) {
            vector<pair<int,int> >::iterator end = it;
            while(end != dolls.end() && end->first == it->first) ++end;

            vector<int> buf;
            while(it != end) {
                buf.push_back(it->second);
                multiset<int>::iterator prev = cur.lower_bound(it->second);
                if(prev != cur.begin()) {
                    --prev;
                    cur.erase(prev);
                }
                ++it;
            }
            cur.insert(buf.begin(), buf.end());
        }

        cout << cur.size() << endl;
    }

    return 0;
}
