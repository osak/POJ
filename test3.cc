#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef complex<double> Point;

namespace std {
bool operator < (const Point &p1, const Point &p2) {
    return p1.real() < p2.real();
}
};

int main() {
    Point p1(100, 200);
    Point p2(200, 300);

    vector<Point> v;
    v.push_back(p1);
    v.push_back(p2);

    sort(v.begin(), v.end());

    cout << (p1<p2) << endl;
    return 0;
}
