//Name: Box
//Level: 2
//Category: 探索
//Note:

#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

struct Pallet {
    int w, h;

    Pallet() {}
    Pallet(int w, int h) : w(w), h(h) {}

    bool operator == (const Pallet &other) const {
        return (w == other.w && h == other.h) || (w == other.h && h == other.w);
    }
};

void impossible() {
    cout << "IMPOSSIBLE" << endl;
    exit(0);
}

int main() {
    Pallet pl[6];
    map<int,int> cnt;
    for(int i = 0; i < 6; ++i) {
        cin >> pl[i].w >> pl[i].h;
        cnt[pl[i].w]++;
        cnt[pl[i].h]++;
    }
    if(cnt.size() > 3) impossible();

    int pos = 0;
    int dims[3];
    for(map<int,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if(it->second % 2 == 1) impossible();
        int c = it->second / 2;
        while(c) {
            dims[pos++] = it->first;
            c -= 2;
        }
    }

    const int W = dims[0], H = dims[1], D = dims[2];
    const Pallet needs[] = { Pallet(W, H), Pallet(W, D), Pallet(H, D) };
    bool used[6] = {0};
    for(int i = 0; i < 3; ++i) {
        int cnt = 0;
        for(int j = 0; j < 6; ++j) {
            if(used[j]) continue;
            if(needs[i] == pl[j]) {
                ++cnt;
                used[j] = true;
                if(cnt == 2) break;
            }
        }
        if(cnt < 2) impossible();
    }

    cout << "POSSIBLE" << endl;
    return 0;
}

