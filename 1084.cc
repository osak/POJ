//Name: Square Destroyer
//Level: 3
//Category: 探索
//Note:

/*
 * 正方形は一つでも辺がなければ破壊されることに注意すると，生き残っている正方形を管理しながら
 * 辺を一つずつ削除していく方法を思いつく．
 * 正方形の場所には意味がなく，構成している辺だけに興味があるので全ての正方形を数え上げ，
 * それぞれを構成する辺をリストアップしておく．
 * あとは枝刈りしながらDFS．このプログラムでは
 * ・現在の最適解より手数がかかるとき
 * ・生き残っている正方形の組み合わせが同じで，過去にこれより少ない手数で到達したとき
 *   (これは辺を左上から削除していく場合のみ合法)
 * ・残りの辺を全て削除しても生き残る正方形が存在するとき
 * に枝刈りしている．
 * また，高速化のためbitsetを使っている．
 *
 * このコードで辺が除かれていない5x5を探索すると少し遅いのだが，POJは問題なく通った．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <map>

using namespace std;

int ans;
map<string,int> memo;
void dfs(int pos, int acc, bitset<55> squares, const vector<bitset<55> > &squareof, const vector<bitset<55> > &accum_square_of) {
    const int N = squareof.size();
    if(acc >= ans) return;
    if(squares.none()) {
        ans = min(ans, acc);
        //cout << ans << endl;
        return;
    }
    if(pos == N) return;
    if((accum_square_of[pos] & squares) != squares) return;

    const string state = squares.to_string();
    if(memo.count(state) && memo[state] <= acc) return;
    memo[state] = acc;

    for(int i = pos; i < N; ++i) {
        bitset<55> res = squares & squareof[i];
        if(res.none()) continue;
        dfs(i+1, acc+1, squares & ~res, squareof, accum_square_of);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        const int edgecnt = 2*N*(N+1);

        // squareof[i] := 辺iが関わっている正方形のリスト
        vector<bitset<55> > squareof(edgecnt);
        int idx = 0;
        for(int row = 0; row < N; ++row) {
            for(int col = 0; col < N; ++col) {
                const int maxsize = min(N-row, N-col);

                for(int size = 1; size <= maxsize; ++size) {
                    int cur = (N+N+1)*row + col;
                    for(int i = 0; i < size-1; ++i) { // Go right
                        squareof[cur].set(idx);
                        cur++;
                    }
                    squareof[cur].set(idx);
                    cur += N+1;
                    for(int i = 0; i < size-1; ++i) { // Go down
                        squareof[cur].set(idx);
                        cur += N+N+1;
                    }
                    squareof[cur].set(idx);
                    cur += N;
                    for(int i = 0; i < size-1; ++i) { // Go left
                        squareof[cur].set(idx);
                        cur--;
                    }
                    squareof[cur].set(idx);
                    cur -= N+1;
                    for(int i = 0; i < size-1; ++i) { // Go up
                        squareof[cur].set(idx);
                        cur -= N+N+1;
                    }
                    squareof[cur].set(idx);
                    ++idx;
                }
            }
        }

        bitset<55> squares;
        for(int i = 0; i < idx; ++i) {
            squares.set(i);
        }

        // accum_square_of[i] := 辺i以降が関わっている正方形のリスト
        vector<bitset<55> > accum_square_of(edgecnt);
        for(int i = 0; i < edgecnt; ++i) {
            //cout << squareof[i].to_string() << endl;
            for(int j = i; j < edgecnt; ++j) {
                accum_square_of[i] |= squareof[j];
            }
        }

        int K;
        cin >> K;
        for(int i = 0; i < K; ++i) {
            int edge;
            cin >> edge;
            --edge;
            squares &= ~squareof[edge];
        }

        ans = 100;
        memo.clear();
        dfs(0, 0, squares, squareof, accum_square_of);
        cout << ans << endl;
    }

    return 0;
}
