#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

double angles[1000];

int main() {
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        angles[i] = i / (double)n;
    }

    //Fix 0th statue
    double prevangle = 0;
    int pos = 1;
    double dist = 0;
    for(int j = 1; j < (n+m); ++j) {
        double angle =  j / (double)(n+m);
        if(prevangle < angles[pos] && angles[pos] < angle) {
            double center = (prevangle + angle) / 2;
            if(angles[pos] < center) dist += 10000 * (angles[pos] - prevangle);
            else dist += 10000 * (angle - angles[pos]);
            if(++pos == n) break;
        }
        prevangle = angle;
    }
    printf("%.4f\n", dist);
}
