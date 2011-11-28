#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;

typedef set<int>::iterator Iterator;

struct Vector {
    int x, y;

    Vector() {}
    Vector(int x, int y) : x(x), y(y) {}

    Vector& operator += (const Vector &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

bool check_x(int x, int dim) {
    return ((dim == 1 || dim == 4) && x > 0) || ((dim == 2 || dim == 3) && x < 0);
}

bool check_y(int y, int dim) {
    return ((dim == 1 || dim == 2) && y > 0) || ((dim == 3 || dim == 4) && y < 0);
}

int x_select(const Vector &cur, set<int> &v, int dim) {
    int dx = 0;
    if((dim == 1 || dim == 4) && cur.x <= 0) {
        Iterator it = v.lower_bound(-cur.x);
        if(it == v.end()) return false;
        dx = *it;
    }
    else if((dim == 2 || dim == 3) && cur.x >= 0) {
        Iterator it = v.lower_bound(cur.x);
        if(it == v.end()) return false;
        dx = -*it;
    }
    else {
        dx = *v.begin();
        if(!check_x(cur.x+dx, dim) || (check_x(cur.x-dx, dim) && abs(cur.x-dx) < abs(cur.x+dx))) dx = -dx;
    }
    v.erase(abs(dx));

    return dx;
}

int y_select(const Vector &cur, set<int> &v, int dim) {
    int dy = 0;
    if((dim == 1 || dim == 2) && cur.y <= 0) {
        Iterator it = v.lower_bound(-cur.y);
        if(it == v.end()) return false;
        dy = *it;
    }
    else if((dim == 3 || dim == 4) && cur.y >= 0) {
        Iterator it = v.lower_bound(cur.y);
        if(it == v.end()) return false;
        dy = -*it;
    }
    else {
        dy = *v.begin();
        if(!check_y(cur.y+dy, dim) || (check_y(cur.y-dy, dim) && abs(cur.y-dy) < abs(cur.y+dy))) dy = -dy;
    }
    v.erase(abs(dy));

    return dy;
}

bool dfs(const Vector &cur, set<int> &v, vector<Vector> &history, const vector<int> &us, int phase) {
    if(phase == us.size()) return true;

    int dim = us[phase];
    for(int i = 0; i < 2; ++i) {
        int dx, dy;
        if(i == 0) {
            dx = x_select(cur, v, dim);
            dy = y_select(cur, v, dim);
        }
        else {
            dy = y_select(cur, v, dim);
            dx = x_select(cur, v, dim);
        }
        Vector ncur = cur;
        ncur += Vector(dx, dy);
        history.push_back(Vector(dx, dy));
        if(dfs(cur, v, history, us, phase+1)) return true;
        else {
            v.insert(abs(dx));
            v.insert(abs(dy));
            history.pop_back();
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    set<int> v;
    vector<int> us(N);
    for(int i = 0; i < 2*N; ++i) {
        int n;
        cin >> n;
        v.insert(n);
    }
    for(int i = 0; i < N; ++i) cin >> us[i];

    Vector cur(0, 0);
    vector<Vector> history;
    if(dfs(cur, v, history, us, 0)) {
        for(int i = 0; i < history.size(); ++i) {
            if(history[i].x > 0) cout << '+';
            cout << history[i].x << ' ';
            if(history[i].y > 0) cout << '+';
            cout << history[i].y << endl;
        }
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}
