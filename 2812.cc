#include <iostream>
#include <complex>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef complex<double> Point;

double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

double area(const vector<Point> &points) {
    double res = 0;
    for(int i = 0; i < points.size(); ++i) {
        int next = (i+1) % points.size();
        res += cross(points[i], points[next]);
    }
    return res/2;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == 0) break;
        
        vector<Point> points;
        for(int i = 0; i < N; ++i) {
            double x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        double volume;
        cin >> volume;

        printf("BAR LENGTH: %.2f\n", abs(volume/area(points)));
    }
    return 0;
}
