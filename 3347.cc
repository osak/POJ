//Name: Kadj Squares
//Level: 4
//Category: 幾何,線分,区間
//Note:

/*
 * 正方形の配置自体は、X軸と正方形に挟まれた三角形に注目してやると
 * この三角形が直角二等辺三角形であることがわかるので、X方向の距離が
 * 求められる。
 * 次に、覆われている判定は、正方形の対角線をすべてX軸上に射影して、
 * 線分を共有している部分を切り取っていく。
 * これを大きい正方形から順に処理していくと、見えない正方形の線分は
 * 長さが0になる。
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define EPS 1e-6

using namespace std;

struct Tag {
    int idx;
    int size;
    double l, r;

    bool operator < (const Tag &other) const {
        return size < other.size;
    }
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<double> xs(N, 0);
        vector<int> sizes(N);

        for(int i = 0; i < N; ++i) {
            cin >> sizes[i];
            if(i == 0) xs[i] = sizes[i] * sqrt(2)/2;
            else {
                for(int j = 0; j < i; ++j) {
                    int e = min(sizes[j], sizes[i]);
                    xs[i] = max(xs[i], xs[j] + e * sqrt(2));
                }
            }
        }
        //for(int i = 0; i < N; ++i) cout << xs[i] << ' ';
        //cout << endl;

        vector<Tag> segs;
        for(int i = 0; i < N; ++i) {
            Tag t;
            t.idx = i+1;
            t.l = xs[i]-sizes[i]*sqrt(2)/2;
            t.r = xs[i]+sizes[i]*sqrt(2)/2;
            t.size = sizes[i];
            segs.push_back(t);
        }
        sort(segs.begin(), segs.end());
        reverse(segs.begin(), segs.end());
        vector<bool> visible(N, true);

        for(int i = 0; i < N; ++i) {
            double il = segs[i].l;
            double ir = segs[i].r;
            for(int j = i+1; j < N; ++j) {
                double l = segs[j].l;
                double r = segs[j].r;
                if(il <= l && l <= ir) segs[j].l = min(ir, r);
                else if(il <= r && r <= ir) segs[j].r= max(il, l);
            }
        }

        vector<int> list;
        for(int i = 0; i < N; ++i) {
            if(abs(segs[i].r - segs[i].l) > EPS) list.push_back(segs[i].idx);
        }
        sort(list.begin(), list.end());
        for(int i = 0; i < list.size(); ++i) cout << list[i] << ' ';
        cout << endl;
#if 0
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            int hide = 0;
            for(int j = 0; j < N; ++j) {
                if(i == j) continue;
                if(sizes[i] >= sizes[j]) continue; //Smaller square cannot cover

                double il = xs[i]-sizes[i]*sqrt(2)/2;
                double ir = xs[i]+sizes[i]*sqrt(2)/2;
                double jl = xs[j]-sizes[j]*sqrt(2)/2-EPS;
                double jr = xs[j]+sizes[j]*sqrt(2)/2+EPS;

                //cout << il << ' ' << ir << ' ' << jl << ' ' << jr << endl;

                if(jl <= xs[i] && xs[i] <= jr) { //Top
                    //hide |= 1; //Top
                    if(jl <= il && il <= jr) hide |= 2; //Left corner
                    if(jl <= ir && ir <= jr) hide |= 4; //Right corner
                }
            }
            if(hide != 6) {
                cout << (i+1) << ' ';
                ++cnt;
            }
        }
        cout << endl;
#endif
    }
    return 0;
}
