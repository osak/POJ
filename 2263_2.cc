#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

struct Tag {
    int cost, best, to;
    Tag() {}
    Tag(int c, int b, int t) : cost(c), best(b), to(t) {}
};

bool operator < (const Tag &t1, const Tag &t2) {
    return t1.cost < t2.cost;
}


map<string, int> name2idx;
vector<bool> used(0, false);
vector<int> maxcost(0, 0);

int bestans[201][201];
int edges[201][201];

int main() {
    for(int C = 1; ; ++C) {
        int curridx = 1;
        int n, r;
        string city1, city2;
        cin >> n >> r;
        if(n == 0 && r == 0) break;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                edges[i][j] = INT_MIN;
            }
        }
        for(int i = 0; i < r; ++i) {
            int c1, c2, dist;
            cin >> city1 >> city2 >> dist;
            c1 = name2idx[city1];
            c2 = name2idx[city2];
            if(c1 == 0) c1 = name2idx[city1] = curridx++;
            if(c2 == 0) c2 = name2idx[city2] = curridx++;

            edges[c1][c2] = edges[c2][c1] = dist;
        }

        cin >> city1 >> city2;
        int start = name2idx[city1];
        int goal = name2idx[city2];

        memcpy(bestans, edges, sizeof(edges));
        for(int k = 1; k <= n; ++k) {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    bestans[i][j] = max(bestans[i][j], min(bestans[i][k], bestans[k][j]));
                }
            }
        }
        
        cout << "Scenario #" << C << endl;
        cout << bestans[start][goal] << " tons" << endl;
        cout << endl;
    }

    return 0;
}
