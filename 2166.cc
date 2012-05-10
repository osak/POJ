//Name: Heapsort
//Level: 2
//Category: シミュレーション,Special Judge
//Note:

/*
 * N要素のヒープからmax-elementを取り除いたとき，siftは最大log(N)回発生する．
 * したがって，N要素をheap sortするときに最大sift回数を与えるheapをv(N)とすると，
 *   v(N+1) := log(N)回siftしてv(N)を生成するヒープ
 * となる．
 * ヒープで一番深い場所は末尾なので，ここに1があればsift回数を最大化できる．
 * あとはv(N+1)の条件よりヒープのsift系列を逆にたどっていくことで
 *   ・ヒープの末尾にある1を上へ持っていく
 *   ・1が先頭まで来たら末尾に飛ばし，先頭には代わりにN+1を入れる
 * とすることでv(N+1)が構築できる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    vector<int> heap(N);
    heap[0] = 1;
    for(int i = 2; i <= N; ++i) {
        int pos = i-2;
        while(true) {
            if(pos == 0) break;
            int parent = (pos-1) / 2;
            swap(heap[pos], heap[parent]);
            pos = parent;
        }
        heap[i-1] = i;
        swap(heap[0], heap[i-1]);
    }

    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << heap[i];
    }
    cout << endl;

    return 0;
}
