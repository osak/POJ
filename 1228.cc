#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

typedef complex<double> Point;

struct PointCmp {
    bool operator ()(const Point &p1, const Point &p2) {
        return p1.real() < p2.real();
    }
};

double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;

        vector<Point> points;
        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        sort(points.begin(), points.end(), PointCmp());
        vector<bool> in_convex(n, false);
        vector<Point> convex(n*2);
        int k = 0;
        for(int i = 0; i < n; ++i) { //Lower hull
            convex[k] = points[i];
            ++k;
            while(k >= 2 && cross(convex[k-1]-convex[k-2], convex[k]-convex[k-1])<0) --k;
        }
        //この時点で一番右の点はconvexに入っている
        for(int i = n-2; i >= 0; --i) { //Upper hull
            convex[k] = points[i];
            ++k;
            while(k >= 2 && cross(convex[k-1]-convex[k-2], convex[k]-convex[k-1])<0) --k;
        }
        convex.resize(k-1);
        for(int i = 0; i < convex.size(); ++i) {
            cout << convex[i] << endl;
        }

        for(int i = 0; i < n; ++i) {
            bool onConvex = false;
            for(int j = 0; j < convex.size(); ++j) {
                if(convex[j] == points[i]) {
                    onConvex = true;
                    break;
                }
                else if(cross(points[i]-convex[j], points[i]-convex[(j+1)%convex.size()])==0) {
                    onConvex = true;
                    break;
                }
            }
            if(!onConvex) {
                cout << "NO" << endl;
                goto next;
            }
        }
        cout << "NO" << endl;
next:
        ;
    }
    return 0;
}
