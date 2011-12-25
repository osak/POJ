//Name: Garland
//Level: 3
//Category: 二分探索
//Note: ちゃんと分かってない．TODO

/*
 * Bの高さの変化は二個目の点の高さの変化と連動している．
 * よって，二個目の点の座標で二分探索すればよい．
 * (あるyでinvaidならy'<yについてもinvalidな理由がよくわかってない)
 */
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Tag {
    int cy2;
    int cy1;
    int c;

    Tag() {}
    Tag(int cy2, int cy1, int c) : cy2(cy2), cy1(cy1), c(c) {}
};

Tag operator +(const Tag &t1, const Tag &t2) {
    return Tag(t1.cy2+t2.cy2, t1.cy1+t2.cy1, t1.c+t2.c);
}

Tag operator -(const Tag &t1, const Tag &t2) {
    return Tag(t1.cy2-t2.cy2, t1.cy1-t2.cy1, t1.c-t2.c);
}

Tag operator *(int n, const Tag &t) {
    return Tag(n*t.cy2, n*t.cy1, n*t.c);
}

int main() {
    int N;
    double A;
    cin >> N >> A;

    double ans = 1e30;
    double left = 0, right = 1e20;
    for(int LOOP = 0; LOOP < 200; ++LOOP) {
        double center = (left+right)/2;
        bool valid = true;
        Tag p1(0, 1, 0);
        Tag p2(1, 0, 0);
        for(int i = 3; i <= N; ++i) {
            Tag tmp = 2*p2 - p1 + Tag(0, 0, 2);
            double h = A*tmp.cy1 + center*tmp.cy2 + tmp.c;
            if(h < 0)  {
                valid = false;
                break;
            }
            p1 = p2;
            p2 = tmp;
        }
        if(!valid) left = center;
        else {
            right = center;
            ans = min(ans, A*p2.cy1 + center*p2.cy2 + p2.c);
        }
    }

    printf("%.2f\n", ans);

    return 0;
}
