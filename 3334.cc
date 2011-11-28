//Name: Connected Gheeves
//Level: 4
//Category: 二分探索,幾何,面積
//Note:

/*
 * 水の量が与えられているので、高さを二分探索して面積を求めながら
 * 目的の水位を探せば良い。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef complex<double> Point;
typedef pair<Point, Point> Line;
typedef pair<Point, Point> Segment;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}


bool intersect(const Point &p11, const Point &p12, const Point &p21, const Point &p22) {
    return (cross(p12-p11, p21-p11)*cross(p12-p11, p22-p11) < 0 &&
            cross(p22-p21, p11-p21)*cross(p22-p21, p12-p21) < 0 );
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
Point crossPoint(const Segment &segment, double y) {
    double dx = segment.first.real() - segment.second.real();
    double dy = segment.first.imag() - segment.second.imag();
    //return Point(segment.second.real() + dx/dy*(y-segment.second.imag()), y);
    return Point(segment.second.real() + dx*(y-segment.second.imag())/dy, y);
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int A;
        cin >> A;
        vector<vector<Point> > gheeves(2);
        vector<int> center(2);
        vector<double> bottom(2, INFINITY);
        double lim;
        for(int i = 0; i < 2; ++i) {
            int n;
            cin >> n;
            gheeves[i].resize(n);
            for(int j = 0; j < n; ++j) {
                cin >> gheeves[i][j].real() >> gheeves[i][j].imag();
                bottom[i] = min(bottom[i], gheeves[i][j].imag());
                if(bottom[i] == gheeves[i][j].imag()) {
                    center[i] = j;
                }
            }
        }

        double high = min(gheeves[0][0].imag(), min(gheeves[0].back().imag(), min(gheeves[1][0].imag(), gheeves[1].back().imag())));
        double low = min(bottom[0], bottom[1]);
        while(high-low > 1e-6) {
            double mid = (high+low) / 2;
            double a = 0;
            for(int g = 0; g < 2; ++g) {
                if(mid <= bottom[g]) continue;
                vector<Point> ps;
                for(int i = 0; i < center[g]; ++i) {
                    if(gheeves[g][i].imag() >= mid && mid >= gheeves[g][i+1].imag()) {
                        ps.push_back(crossPoint(Segment(gheeves[g][i], gheeves[g][i+1]), mid));
                        for(int j = i+1; j < center[g]; ++j) ps.push_back(gheeves[g][j]);
                        break;
                    }
                }
                for(int i = center[g]; i < gheeves[g].size()-1; ++i) {
                    ps.push_back(gheeves[g][i]);
                    if(gheeves[g][i].imag() <= mid && mid <= gheeves[g][i+1].imag()) {
                        ps.push_back(crossPoint(Segment(gheeves[g][i], gheeves[g][i+1]), mid));
                        break;
                    }
                }
                a += area(ps);
            }
            //cout << high << ' ' << low << endl;
            //cout << a << endl;
            if(a < A) low = mid;
            else high = mid;
        }

end:
        printf("%.3f\n", (high+low)/2);
    }
    return 0;
}
