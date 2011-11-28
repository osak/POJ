#include <iostream>
#include <complex>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef complex<double> Point;
typedef pair<Point, Point> Line;

const double EPS = 1e-7;

bool EQV(double d1, double d2) {
    return abs(d1-d2) < EPS;
}

bool cmp(const Point &p1, const Point &p2) {
    if(!EQV(p1.real(), p2.real())) return p1.real() < p2.real();
    else return p1.imag() < p2.imag();
}

double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}
int ccw(const Point &v1, const Point &v2, const Point &v3) {
    double tmp = cross(v2-v1, v3-v1);
    if(tmp > 0) return 1;
    else if(tmp < 0) return -1;
    return 0;
}

vector<Point> convex_hull(const vector<Point> &av) {
    vector<Point> v = av;
    sort(v.begin(), v.end(), cmp);
    vector<Point> res(v.size());
    int k = 0;
    for(int i = 0; i < v.size(); ++i) {
        while(k >= 2 && ccw(res[k-2], res[k-1], v[i]) >= 0) --k;
        res[k++] = v[i];
    }
    res.resize(k);

    return res;
}

double vdist(const Line &l, const Point &p) {
    const Point vec = l.second - l.first;
    double a = vec.imag() / vec.real();
    return abs(p.imag() - (l.first.imag() + a*(p.real() - l.first.real())));
}

int main() {
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<Point> v;
        for(int i = 0; i < N; ++i) {
            double x, y;
            cin >> x >> y;
            v.push_back(Point(x, y));
        }

        vector<Point> cvx = convex_hull(v);
        vector<Line> lines;
        vector<vector<double> > dist(cvx.size()-1, vector<double>(N));
        for(int i = 0; i < cvx.size()-1; ++i) {
            Line l = Line(cvx[i], cvx[i+1]);
            lines.push_back(l);

            for(int j = 0; j < v.size(); ++j) {
                dist[i][j] = vdist(l, v[j]);
        //        cout << dist[i][j] << " ";
            }
        //    cout << endl;
        }

        double maxdist = 0;
        double left = 0, right = 1e8;
        while(right-left > 1e-6) {
            vector<bool> used(lines.size(), false);
            vector<bool> fulfilled(v.size(), false);
            vector<double> mdists(v.size(), 1e8);
            int fulfillcnt = 0;
            double center = (left+right) / 2;
            double ans = 0;

            for(int k = 0; k < K; ++k) {
                int mxfulfill = 0;
                double mxdist = 1e9;
                int bestline = 0;
                for(int i = 0; i < lines.size(); ++i) {
                    int fcnt = 0;
                    double fmdist = 0;
                    if(used[i]) continue;
                    for(int j = 0; j < v.size(); ++j) {
                        if(fulfilled[j]) continue;
                        if(dist[i][j] <= center+EPS) {
                            ++fcnt;
                            fmdist = max(fmdist, min(dist[i][j], mdists[j]));
                        }
                    }
                    if(mxfulfill <= fcnt) {
                        if(mxfulfill < fcnt) {
                            mxfulfill = fcnt;
                            mxdist = fmdist;
                            bestline = i;
                        }
                    }
                }
                for(int i = 0; i < v.size(); ++i) {
                    if(!fulfilled[i] && dist[bestline][i] <= center+EPS) {
                        fulfilled[i] = true;
                        fulfillcnt++;
                        mdists[i] = min(mdists[i], dist[bestline][i]);
                    }
                }
                used[bestline] = true;
            }
            
            if(fulfillcnt < N) left = center;
            else {
                maxdist = 0;
                for(int i = 0; i < v.size(); ++i) 
                    maxdist = max(maxdist, mdists[i]);
                right = center;
            }
        }
        /*
        for(int k = 0; k < K; ++k) {
            double md = 1e8;
            int best = 0;
            for(int i = 0; i < lines.size(); ++i) {
                if(used[i]) continue;
                double d = 0;
                for(int j = 0; j < v.size(); ++j) {
                    if(dist[i][j] < mdists[j])
                        d = max(d, dist[i][j]);
                }
                if(d < md) {
                    best = i;
                    md = d;
                }
            }
            cout << best << endl;
            for(int j = 0; j < v.size(); ++j) {
                mdists[j] = min(mdists[j], dist[best][j]);
                maxdist = max(maxdist, mdists[j]);
            }
            used[best] = true;
        }
        */

        printf("%.3f\n", maxdist);
    }
    return 0;
}
