//Name: Transmitters
//Level: 2
//Category: しゃくとり法
//Note:

/*
 * 必ず1点は半径上に乗っているはずなので、一箇所調べたら次の角度は
 * 点と半径がぶつかるところになる。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> Point;

//const double M_PI = 3.1415926;

bool operator< (const Point &p1, const Point &p2) {
    return arg(p1) < arg(p2);
}

int main() {
    while(true) {
        double x, y, radius;
        int N;
        cin >> x >> y >> radius;
        if(radius < 0) break;
        cin >> N;

        Point center = Point(x, y);
        vector<double> args;
        for(int i = 0; i < N; ++i) {
            double px, py;
            cin >> px >> py;
            Point p = Point(px, py)-center;
            if(abs(p) > radius) continue;
            args.push_back(arg(p));
            //cout << points[i] << " " << arg(points[i]) << endl;
        }
        sort(args.begin(), args.end());
        /*
        for(int i = 0; i < args.size(); ++i) {
            cout << args[i] << endl;
        }
        */
        int cnt = 0;
        int best = 0;
        int left = 0, right = 0;
        while(left < args.size()) {
            int orgright = right;
            while(args[right]-args[left] <= M_PI) {
                ++cnt;
                right = (right+1)%args.size();
                if(right == orgright) break;
            }
            if(cnt > best) best = cnt;
            //cout << left << ":" << cnt << endl;
            args[left] += M_PI*2;
            //cout << left << ":" << cnt << endl;
            ++left;
            --cnt;
        }
        cout << best << endl;
    }
    return 0;
}
