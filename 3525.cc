#include <iostream>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> Point;

inline double ccw(const Point &p1, const Point &p2, const Point &p3) {
    const Point v1 = p2-p1;
    const Point v2 = p3-p2;
    return v1.real()*v2.imag() - v1.imag()*v2.real();
}

void shrink(const vector<Point> &vs, vector<Point> &res, double a) {
    res.clear();
    for(int i = 0; i < vs.size(); ++i) {
        const Point &p1 = vs[i];
        const Point &p0 = i>0 ? vs[i-1] : vs[(int)vs.size()-1];
        const Point &p2 = i+1<vs.size() ? vs[i+1] : vs[0];

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Point> vs(N);
        for(int i = 0; i < N; ++i) {
            cin >> vs[i].real() >> vs[i].imag();
        }
