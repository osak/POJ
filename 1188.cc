//Name: Gleaming the Cubes
//Level: 2
//Category: 数学
//Note:

/*
 * 全ての立方体の共通部分を求めるだけなので，共通部分だけを記憶して逐次処理すればよい．
 * それぞれの座標軸は独立なので，各座標軸ごとに共通範囲を求める．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

struct Box {
    int pos[3];
    int len[3];

    Box() {}

    Box operator &=(const Box &other) {
        for(int i = 0; i < 3; ++i) {
            int np = max(pos[i], other.pos[i]);
            int nl = min(pos[i]+len[i], other.pos[i]+other.len[i]) - np;
            if(nl < 0) nl = 0;

            pos[i] = np;
            len[i] = nl;
        }
        return *this;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        Box b;
        for(int i = 0; i < 3; ++i) {
            b.pos[i] = 0;
            b.len[i] = INT_MAX;
        }

        while(N--) {
            Box nb;
            int len;
            for(int i = 0; i < 3; ++i) {
                cin >> nb.pos[i];
            }
            cin >> len;
            for(int i = 0; i < 3; ++i) {
                nb.len[i] = len;
            }

            b &= nb;
        }

        cout << b.len[0]*b.len[1]*b.len[2] << endl;
    }

    return 0;
}
