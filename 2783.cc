//Name: On Storing Clothes
//Level: 3
//Category: シミュレーション
//Note:

/*
 * 実装が面倒臭い。
 * 自分がハマった点は、
 * ・洗濯物を引き出したあとのカーソル位置は移動しない（カーソルはkの先頭であり、末尾に移動はしない）
 * ・ちょうど一周した＝空きスペースがないとは言えない
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    int L;
    cin >> L;
    vector<int> rail(N, 0);
    int pos = 0;
    while(L--) {
        char op;
        int n;
        cin >> op >> n;
        if(op == 'D') {
            int cnt = 0;
            int on_the_go = 0;
            for(; on_the_go < 3*N; pos=(pos+1)%N) {
                if(rail[pos]) cnt = 0;
                else ++cnt;
                if(cnt == n+2) break;
                ++on_the_go;
            }
            //if(pos == org && !rail[pos]) ++cnt;
            if(cnt != n+2) {
                cout << "No space left, please come back later." << endl;
            }
            else {
                for(int i = 0; i < n; ++i) {
                    rail[(pos-i-1+N)%N] = 1;
                }
                cout << "The launderer gives ticket " << (pos-n-1+N)%N << "." << endl;
            }
        }
        else {
            cout << "The launderer gives back batch " << n << "." << endl;
            if(!rail[(n-1+N)%N]) cout << n << " is freed." << endl;
            for(pos = (n+1)%N; rail[pos]; pos=(pos+1)%N) {
                rail[pos] = 0;
                cout << pos << " is freed." << endl;
            }
            if(!rail[(pos+1)%N]) cout << pos << " is freed." << endl;
            pos = n;
        }
    }
    return 0;
}
