#include <iostream>
#include <vector>
#include <complex>
#include <queue>
#include <cstdio>

using namespace std;

typedef complex<double> Point;

vector<Point> points;
double dists[100][100];
bool used[100];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            dists[i][j] = dists[j][i] = abs((points[j]-points[i]));
        }
    }

    double total = 0;
    priority_queue<pair<double, int> > q;
    for(int i = 0; i < n; ++i) {
        q.push(make_pair(-dists[0][i], i));
    }
    used[0] = true;
    while(!q.empty()) {
        double cost = q.top().first;
        int idx = q.top().second;
        q.pop();

        if(used[idx]) continue;
        used[idx] = true;
        total += cost;
        for(int i = 0; i < n; ++i) {
            if(used[i]) continue;
            q.push(make_pair(-dists[idx][i], i));
        }
    }

    printf("%.2lf\n", -total);

    return 0;
}
