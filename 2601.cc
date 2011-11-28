//Name: Simple calculations
//Level: 1
//Category: 数列,二分探索
//Note:

/*
 * 明らかにa1を増加させるとanも増加する．
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

double calc(double a0, double a1, const vector<double> &c, const int N) {
    for(int i = 1; i <= N; ++i) {
        double next = 2*a1 - a0 + 2*c[i];
        a0 = a1;
        a1 = next;
    }
    return a1;
}

int main() {
    int N;
    cin >> N;

    double a0, an;
    vector<double> c(N+1);
    cin >> a0 >> an;
    for(int i = 1; i <= N; ++i) cin >> c[i];

    double left = -1000, right = 1000;
    while(right-left > 1e-3) {
        double center = (left+right) / 2;
        double tmp = calc(a0, center, c, N);
        if(tmp > an) right = center;
        else left = center;
    }
    printf("%.2f\n", (left+right)/2);

    return 0;
}
