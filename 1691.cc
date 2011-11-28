#include <iostream>
#include <vector>
#include <queue>
#include <complex>
#include <climits>
#include <cstdio>

using namespace std;

struct Rectangle {
    int top, left, bottom, right, color;
    Rectangle() {}
    Rectangle(int t, int l, int b, int r, int c) : top(t), left(l), bottom(b), right(r), color(c){}
};

int main() {
    int cases;
    cin >> cases;
    while(cases--) {
        int N;
        cin >> N;

        vector<Rectangle> rectangles;
        for(int i = 0; i < N; ++i) {
            int ly, lx, ry, rx, color;
            cin >> ly >> lx >> ry >> rx >> color;
            rectangles.push_back(Rectangle(ly, lx, ry, rx, color));
        }

        vector<unsigned> upper(N, 0);
        for(int i = 0; i < N; ++i) {
            unsigned upper_flg = 0;
            for(int j = 0; j < N; ++j) {
                if(rectangles[j].bottom == rectangles[i].top &&
                        rectangles[j].left <= rectangles[i].right && rectangles[j].right >= rectangles[i].left)
                {
                    upper_flg |= (1<<j);
                }
            }
            upper[i] = upper_flg;
        }

        vector<vector<bool> > visited(1<<N, vector<bool>(21, false));
        priority_queue<pair<int, pair<unsigned, int> > > q;
        q.push(make_pair(0, make_pair(0, 0)));
        while(!q.empty()) {
            int cost = q.top().first;
            unsigned state = q.top().second.first;
            int color = q.top().second.second;
            q.pop();

            if(visited[state][color]) continue;
            visited[state][color] = true;
            if(state == (1<<N)-1) {
                cout << -cost << endl;
                break;
            }

            for(int i = 0; i < N; ++i) {
                if(state & (1<<i)) continue;
                if((state & upper[i]) != upper[i]) continue;
                if(rectangles[i].color == color) {
                    q.push(make_pair(cost, make_pair(state | (1<<i), color)));
                }
                else {
                    q.push(make_pair(cost-1, make_pair(state | (1<<i), rectangles[i].color)));
                }
            }
        }
    }

    return 0;
}

