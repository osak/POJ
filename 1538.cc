//Name: Extrapolation Using a Difference Table
//Level: 2
//Category: やるだけ
//Note:

/*
 * 最初にテーブルを作る．
 * 列の追加は，一番下の列だけを覚えておけばできる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> terms(N);
        for(int i = 0; i < N; ++i) {
            cin >> terms[i];
        }
        int K;
        cin >> K;

        vector<vector<int> > table(N, vector<int>(N));
        table[0] = terms;
        for(int i = 1; i < N; ++i) {
            for(int j = 0; j < N-i; ++j) {
                table[i][j] = table[i-1][j+1] - table[i-1][j];
            }
        }

        vector<int> buf(N), work(N);
        for(int i = 0; i < N; ++i) {
            buf[i] = table[i][N-i-1];
        }

        for(int k = 0; k < K; ++k) {
            work[N-1] = buf[N-1];
            for(int i = N-2; i >= 0; --i) {
                work[i] = buf[i] + work[i+1];
            }
            buf.swap(work);
        }

        cout << "Term " << (N+K) << " of the sequence is " << buf[0] << endl;
    }

    return 0;
}
