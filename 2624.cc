#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;

typedef complex<double> Point;

int main() {
    while(true) {
        Point p[2][2];
        for(int i = 0; i < 4; ++i) {
            double x, y;
            if(scanf("%lf %lf", &x, &y) != 2) return 0;
            p[i/2][i&1] = Point(x, y);
        }
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                if(p[0][i] == p[1][j]) {
                    Point pp = p[0][1-i]+p[1][1-j]-p[0][i];
                    printf("%.3f %.3f\n", pp.real(), pp.imag());
                    goto end;
                }
            }
        }
    end:
        ;
    }
    return 0;
}
