#include <iostream>
#include <vector>
#include <complex>
#include <utility>
#include <algorithm>

using namespace std;

typedef complex<double> Point;
typedef pair<Point, Point> Line;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}


bool intersect(const Point &p11, const Point &p12, const Point &p21, const Point &p22) {
    //点が線分上判定
    if(abs(cross(p12-p11, p21-p11)) <= 1e-8 && norm(p12-p11) <= norm(p21-p11)) return true;
    if(abs(cross(p12-p11, p22-p11)) <= 1e-8 && norm(p12-p11) <= norm(p22-p11)) return true;
    if(abs(cross(p22-p21, p11-p21)) <= 1e-8 && norm(p22-p21) <= norm(p11-p21)) return true;
    if(abs(cross(p22-p21, p12-p21)) <= 1e-8 && norm(p22-p21) <= norm(p12-p21)) return true;

    /*
    //同一直線上判定
    if(cross(p12-p11, p21-p11) == 0 && cross(p12-p11, p22-p11) == 0) {
        if(max(p11.real(), p12.real()) <= min(p21.real(), p22.real())) return true;
        else return false;
    }
    if(cross(p22-p21, p11-p21) == 0 && cross(p22-p21, p12-p21) == 0) {
        if(max(p11.real(), p12.real()) <= min(p21.real(), p22.real())) return true;
        else return false;
    }
    */

    return (cross(p12-p11, p21-p11)*cross(p12-p11, p22-p11) < 0 &&
            cross(p22-p21, p11-p21)*cross(p22-p21, p12-p21) < 0 );
}

bool intersect_line_seg(const Line &line, const Line &seg) {
    double minx = min(seg.first.real(), seg.second.real());
    double miny = min(seg.first.imag(), seg.second.imag());
    double maxx = max(seg.first.real(), seg.second.real());
    double maxy = max(seg.first.imag(), seg.second.imag());

    const Point v = line.second - line.first;
    const Point s1 = line.first + v*((minx - line.first.real())/v.real());
    const Point s2 = line.first + v*((maxx - line.first.real())/v.real());
    return intersect(s1, s2, seg.first, seg.second);
}

int main() {
    int C;
    cin >> C;
    while(C--) {
        int N;
        cin >> N;

        vector<Line> lines;
        while(N--) {
            Line l;
            cin >> l.first.real() >> l.first.imag() >> l.second.real() >> l.second.imag();
            lines.push_back(l);
        }

        bool ok = true;
        for(int i = 0; i < lines.size(); ++i) {
            for(int j = i+1; j < lines.size(); ++j) {
                ok = true;
                Point p11 = lines[i].first;
                Point p12 = lines[i].second;
                Point p21 = lines[j].first;
                Point p22 = lines[j].second;

                for(int k = 0; k < lines.size(); ++k) {
                    if(!intersect_line_seg(Line(p11, p21), lines[k]) &&
                       !intersect_line_seg(Line(p11, p22), lines[k]) &&
                       !intersect_line_seg(Line(p12, p21), lines[k]) &&
                       !intersect_line_seg(Line(p12, p22), lines[k])) {
                        ok = false;
                        goto next;
                    }
                }
next:
                if(ok) goto end;
            }
        }
end:
        cout << (ok?"Yes!":"No!") << endl;
    }
    return 0;
}
