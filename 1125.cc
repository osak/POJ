#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Tag {
    int sum, cost, person;
    Tag() {}
    Tag(int s, int c, int p) : sum(s), cost(c), person(p) {}
};

bool operator <(const Tag &t1, const Tag &t2) {
    return t2.sum < t1.sum;
}

vector<vector<pair<int, int> > > connection;
vector<bool> used(0, false);

int main() {
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        connection.clear();
        connection.resize(n+1);
        for(int i = 1; i <= n; ++i) {
            int m;
            cin >> m;
            for(int j = 1; j <= m; ++j) {
                int to, cost;
                cin >> to >> cost;
                connection[i].push_back(make_pair(cost, to));
            }
        }
        int beststart = -1;
        int besttime = INT_MAX;

        for(int i = 1; i <= n; ++i) {
            priority_queue<Tag> q;
            int maxcost = 0;

            for(int j = 0; j < connection[i].size(); ++j) {
                q.push(Tag(connection[i][j].first, connection[i][j].first, connection[i][j].second));
            }
            used.clear();
            used.resize(n+1);
            for(int j = 0; j <= n; ++j) used[j] = false;
            used[i] = true;
            while(!q.empty()) {
                Tag t = q.top();
                q.pop();
                if(used[t.person]) continue;
                used[t.person] = true;

                if(t.sum > maxcost) maxcost = t.sum;
                //cout << t.cost << " " << t.person << endl;
                //if(i == 3) cout << t.person << " " << t.sum << endl;
                for(int j = 0; j < connection[t.person].size(); ++j) {
                    if(used[connection[t.person][j].second]) continue;
                    q.push(Tag(t.sum+connection[t.person][j].first, connection[t.person][j].first, connection[t.person][j].second));
                }
            }
            bool ok = true;
            for(int j = 1; j <= n; ++j) {
                if(!used[j]) {
                    ok = false;
                    break;
                }
            }
            if(ok && besttime > maxcost) {
                besttime = maxcost;
                beststart = i;
            }
        }
        if(beststart == -1) {
            cout << "disjoint" << endl;
        }
        else {
            cout << beststart << " " << besttime << endl;
        }
    }

    return 0;
}
