//Name: Cows
//Level: 2
//Category: 幾何,凸包,面積,convex hull
//Note: 牛だけどFarmer Johnではない

/*
 * ライブラリゲー。
 * 凸包を求めて面積を出し、50で割るだけ。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

typedef complex<double> Point;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

//Verified AOJ 0012
double ccw(const Point &p1, const Point &p2, const Point &p3) {
    return cross(p2-p1, p3-p1);
}

//Verified PKU 2812
double area(const vector<Point> &points) {
    double res = 0;
    for(int i = 0; i < points.size(); ++i) {
        int next = (i+1) % points.size();
        res += cross(points[i], points[next]);
    }
    return res/2;
}

bool cmp(const Point &p1, const Point &p2) {
    return p1.real() < p2.real();
}

vector<Point> convex_hull(const vector<Point> &points) {
    int N = points.size();
    vector<Point> v = points;
    sort(v.begin(), v.end(), cmp);
    vector<Point> hull(2*N);
    int pos = 0;
    for(int i = 0; i < N; ++i) {
        while(pos >= 2 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    int lim = pos;
    for(int i = N-2; i >= 0; --i) {
        while(pos >= lim+1 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    hull.erase(hull.begin()+pos, hull.end());
    return hull;
}

int main() {
    int N;
    cin >> N;
    vector<Point> v(N);
    for(int i = 0; i < N; ++i) cin >> v[i].real() >> v[i].imag();
    cout << (int)(area(convex_hull(v))/50) << endl;
    return 0;
}
