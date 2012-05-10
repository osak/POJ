//Name: Gunman
//Level: 3
//Category: 幾何
//Note:

/*
 * x方向とy方向は別々に考えてよい．
 *
 * 発射地点はxのみ自由でy,zは0固定であることから，
 *   ・x-z平面(x方向に伸びる線分を考える)で全ての線分を貫通するには，
 *     2N個の端点のうちどれか2つを通る直線だけを考えればよい．
 *   ・y-z平面(y方向に伸びる線分を考える)で全ての線分を貫通するには，
 *     2N個の端点のどれかと原点(y=0,z=0)を通る直線だけを考えればよい．
 * あとは実装するだけ．入力が整数座標なので誤差死はあまり怖くない．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <complex>
#include <cstdlib>

using namespace std;

typedef complex<double> Point;
typedef pair<Point,Point> Segment;

struct Window {
    Point lt, rb;
    double z;
};

void unsolvable() {
    cout << "UNSOLVABLE" << endl;
    exit(0);
}

vector<double> ans_x;
double ans_init_x;
// p1(x,z), p2(x,z)
bool check_x(const Point &p1, const Point &p2, const vector<Window> &windows) {
    ans_x.clear();
    Point dt = p2 - p1;
    for(int i = 0; i < windows.size(); ++i) {
        const Window &w = windows[i];
        const Point p = p1 + dt*(w.z-p1.imag())/dt.imag();
        if(w.lt.real() <= p.real() && p.real() <= w.rb.real()) {
            ans_x.push_back(p.real());
        }
        else {
            return false;
        }
    }
    ans_init_x = (p1 + dt*(0-p1.imag())/dt.imag()).real();
    return true;
}

vector<double> ans_y;
// p1(y, z)
bool check_y(const Point &p1, const vector<Window> &windows) {
    ans_y.clear();
    Point dt = p1;
    for(int i = 0; i < windows.size(); ++i) {
        const Window &w = windows[i];
        const Point p = dt*w.z/dt.imag();
        if(w.lt.imag() <= p.real() && p.real() <= w.rb.imag()) {
            ans_y.push_back(p.real());
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<Window> windows(N);
    for(int i = 0; i < N; ++i) {
        Window &w = windows[i];
        cin >> w.lt.real() >> w.lt.imag() >> w.rb.real() >> w.rb.imag() >> w.z;
    }

    // x方向はどれか2つの端点を通る
    Segment xsol;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
#define CHECK(a,b) do { \
    Point p1(windows[i].a.real(), windows[i].z); \
    Point p2(windows[j].b.real(), windows[j].z); \
    if(check_x(p1,p2,windows)) { \
         goto y_check; \
    } \
} while(0);

            CHECK(lt, lt);
            CHECK(lt, rb);
            CHECK(rb, lt);
            CHECK(rb, rb);
        }
#undef CHECK
    }
    unsolvable();

y_check:
    // y方向はどれか1つの端点を通る
    Point ysol;
    for(int i = 0; i < N; ++i) {
#define CHECK(a) do { \
    Point p1(windows[i].a.imag(), windows[i].z); \
    if(check_y(p1,windows)) { \
         goto last; \
    } \
} while(0);
        CHECK(lt);
        CHECK(rb);
    }
    unsolvable();
    
last:
    cout << "SOLUTION" << endl;
    cout.precision(6);
    cout.setf(ios::fixed);
    cout << ans_init_x << endl;
    for(int i = 0; i < N; ++i) {
        cout << ans_x[i] << ' ' << ans_y[i] << ' ' << windows[i].z << endl;
    }

    return 0;
}
