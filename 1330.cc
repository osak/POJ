//Name: Nearest Common Ancestors
//Level: 2
//Category: 探索,木構造,グラフ
//Note:

/*
 * それぞれのノードについて親を覚えておき，子から親へのパスを探す．
 * 2本のパスを逆から見ていき，食い違うところの直前が求めるノード．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> roots(N+1, -1);
        for(int i = 0; i < N-1; ++i) {
            int a, b;
            cin >> a >> b;
            roots[b] = a;
        }

        int a, b;
        cin >> a >> b;
        vector<int> va, vb;
        va.push_back(-1); //番兵
        do {
            va.push_back(a);
            a = roots[a];
        } while(a != -1);
        vb.push_back(-2); //番兵
        do {
            vb.push_back(b);
            b = roots[b];
        } while(b != -1);

        reverse(va.begin(), va.end());
        reverse(vb.begin(), vb.end());
        for(int i = 0; i < min(va.size(), vb.size()); ++i) {
            if(va[i] != vb[i]) {
                cout << va[i-1] << endl;
                break;
            }
        }
    }
    return 0;
}
