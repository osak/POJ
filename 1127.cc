//Name: Jack Straws
//Level: 2
//Category: Union Find,幾何,交差判定
//Note:

/*
 * 線分どうしの交差判定ができれば、あとはUnion Findでまとめれば良い。
 */
#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

typedef complex<int> Point;
typedef pair<Point, Point> Edge;

bool intersect(const Edge &e1, const Edge &e2) {
    const Point v1 = e1.second - e1.first;
    const Point v2 = e2.second - e2.first;
    const Point v11 = e2.first - e1.first;
    const Point v12 = e2.second - e1.first;
    const Point v21 = e1.first - e2.first;
    const Point v22 = e1.second - e2.first;

    int c1 = (v1.real()*v11.imag()-v1.imag()*v11.real()) * (v1.real()*v12.imag()-v1.imag()*v12.real());
    int c2 = (v2.real()*v21.imag()-v2.imag()*v21.real()) * (v2.real()*v22.imag()-v2.imag()*v22.real());
    if(c1 == 0 && c2 == 0) {
        if(min(e1.first.real(), e1.second.real()) > max(e2.first.real(), e2.second.real())) return false;
        if(min(e1.first.imag(), e1.second.imag()) > max(e2.first.imag(), e2.second.imag())) return false;
        if(max(e1.first.real(), e1.second.real()) < min(e2.first.real(), e2.second.real())) return false;
        if(max(e1.first.real(), e1.second.real()) < min(e2.first.real(), e2.second.real())) return false;
    }
    return (c1 <= 0 && c2 <= 0);
}

vector<int> roots;
vector<int> level;

int getroot(int idx) {
    if(roots[idx] == idx) return idx;
    return roots[idx] = getroot(roots[idx]);
}

void unite(int n1, int n2) {
    int r1 = getroot(n1);
    int r2 = getroot(n2);
    if(level[r1] < level[r2]) {
        roots[r1] = r2;
    }
    else {
        roots[r2] = r1;
        if(level[r1] == level[r2]) ++level[r1];
    }
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == 0) break;

        vector<Edge> edges;
        roots.resize(N);
        level.resize(N);
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            edges.push_back(make_pair(Point(x1, y1), Point(x2, y2)));
            roots[i] = i;
            level[i] = 0;
        }

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                int r1 = getroot(i);
                int r2 = getroot(j);
                if(r1 == r2) continue;
                if(intersect(edges[i], edges[j])) {
                    unite(r1, r2);
                }
            }
        }

        while(true) {
            int a, b;
            cin >> a >> b;
            if(a == 0) break;
            if(getroot(a-1) == getroot(b-1)) {
                cout << "CONNECTED" << endl;
            }
            else {
                cout << "NOT CONNECTED" << endl;
            }
        }
    }
    return 0;
}
