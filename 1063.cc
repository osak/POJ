//Name: Flip and Shift
//Level: 2
//Category: 数論
//Note:

/*
 * Flipは連続した3つの数字列の中で、両端の2つを入れ替える操作。
 * Kが偶数の時、最初に偶数番目にあった数字は偶数番目、奇数番目の数字は奇数番目にしか移動できない。
 * Kが奇数の時、一周すれば偶奇が反転する。
 * 同じ数字が一列に並んだときは、偶数番目と奇数番目の個数は高々1個差でないといけない。
 */
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        int odd = 0, even = 0;
        int K;
        cin >> K;
        for(int i = 0; i < K; ++i) {
            int n;
            cin >> n;
            if(n) {
                if(i & 1) odd++;
                else even++;
            }
        }
        if((K&1) || abs(odd-even) <= 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
