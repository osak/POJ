//Name: The Doors
//Level: 3
//Category: グラフ,最短経路,幾何,交差判定
//Note:

/*
 * 壁の端点をノードと見てグラフを作り，最短経路を求める．
 * その際，直線移動で壁に当たらないように線分の交差判定を使う．
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <complex>
#include <utility>

using namespace std;

typedef complex<double> Point;
typedef pair<Point,Point> Line;

double ccw(const Point &p1, const Point &p2, const Point &p3) {
    Point v1 = p2-p1;
    Point v2 = p3-p1;
    return v1.real()*v2.imag() - v1.imag()*v2.real();
}

bool intersect(const Line &l1, const Line &l2) {
    return ccw(l1.first, l1.second, l2.first) * ccw(l1.first, l1.second, l2.second) < 0 && 
           ccw(l2.first, l2.second, l1.first) * ccw(l2.first, l2.second, l1.second) < 0;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == -1) break;

        vector<Line> ls;
        vector<Point> ps;
        ps.push_back(Point(0, 5));
        for(int i = 0; i < N; ++i) {
            double X;
            cin >> X;
            vector<Point> tmp;
            for(int j = 0; j < 4; ++j) {
                Point p(X, 0);
                cin >> p.imag();
                tmp.push_back(p);
                ps.push_back(p);
            }
            ls.push_back(make_pair(Point(X, 0), tmp[0]));
            ls.push_back(make_pair(tmp[1], tmp[2]));
            ls.push_back(make_pair(tmp[3], Point(X, 10)));
        }
        ps.push_back(Point(10, 5));
        vector<vector<double> > dist(ps.size(), vector<double>(ps.size(), 1e10));
        for(int i = 0; i < ps.size(); ++i) {
            for(int j = i; j < ps.size(); ++j) {
                if(ps[i].real() >= ps[j].real()) continue;
                Line lc(ps[i], ps[j]);
                bool valid = true;
                for(int k = 0; k < ls.size(); ++k) {
                    if(intersect(lc, ls[k])) {
                        valid = false;
                        break;
                    }
                }
                if(valid) dist[i][j] =  abs(ps[i]-ps[j]);
            }
        }
        for(int k = 0; k < ps.size(); ++k)
            for(int i = 0; i < ps.size(); ++i)
                for(int j = 0; j < ps.size(); ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        printf("%.2f\n", dist[0][ps.size()-1]);
    }
    return 0;
}
