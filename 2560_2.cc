#include <iostream>
#include <vector>
#include <complex>
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef complex<double> Point;

struct Edge {
    int a, b;
    double length;

    Edge() {}
    Edge(int aa, int bb, double l) : a(aa), b(bb), length(l) {}
};

bool operator < (const Edge &e1, const Edge &e2) {
    return e1.length < e2.length;
}

vector<Point> points;
vector<Edge> edges;
vector<int> root;
vector<int> rank;
bool used[100];

int getroot(int node) {
    if(root[node] == node) return node;
    else return root[node] = getroot(root[node]);
}

void unionroot(int a, int b) {
    if(rank[a] > rank[b]) {
        root[b] = a;
    }
    else {
        root[a] = b;
        if(rank[a] == rank[b]) {
            ++rank[b];
        }
    }
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            edges.push_back(Edge(i, j, abs(points[j]-points[i])));
        }
    }
    sort(edges.begin(), edges.end());

    double total = 0;
    root.resize(n);
    rank.resize(n);
    for(int i = 0; i < n; ++i) {
        root[i] = i;
        rank[i] = 0;
    }
    for(int i = 0; i < edges.size(); ++i) {
        //Union find
        int roota = getroot(edges[i].a);
        int rootb = getroot(edges[i].b);
        if(roota != rootb) {
            total += edges[i].length;
            unionroot(root[edges[i].a], root[edges[i].b]);
        }
    }

    printf("%.2lf\n", total);

    return 0;
}
