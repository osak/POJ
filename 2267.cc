#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <climits>

using namespace std;

bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

struct Tag {
    int cost;
    int hour;
    int pos;

    Tag() {}
    Tag(int c, int h, int p) : cost(c), hour(h), pos(p) {}

    bool operator < (const Tag &other) const {
        return cost > other.cost;
    }
};

struct Road {
    int start, end;
    int eidx;

    Road() {}
    Road(int s, int e, int eidx) : start(s), end(e), eidx(eidx) {}

    bool valid() const {
        if(!inRange(18, start, 24) && !inRange(0, start, 6)) return false;
        if(!inRange(18, end, 24) && !inRange(0, end, 6)) return false;
        for(int i = start; i != end; i=(i+1)%24) {
            //if(i == 24) i = 0;
            if(!inRange(18, i, 24) && !inRange(0, i, 6)) return false;
        }
        //if(((end+24)-start) % 24 > 12) return false;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(0);

    int C;
    cin >> C;
    for(int CASE = 1; CASE <= C; ++CASE) {
        map<string, int> dict;
        int idx = 0;

        int N;
        cin >> N;

        vector<vector<Road> > roads(N+1);
        for(int i = 0; i < N; ++i) {
            string s1, s2;
            int sidx, eidx;
            int s, e;
            cin >> s1 >> s2 >> s >> e;
            if(dict[s1] == 0) dict[s1] = ++idx;
            if(dict[s2] == 0) dict[s2] = ++idx;
            sidx = dict[s1];
            eidx = dict[s2];
            if(e > 12) continue;

            e += s;
            s %= 24;
            e %= 24;

            Road r(s, e, eidx);
            if(r.valid()) {
                roads[sidx].push_back(r);
            }
        }

        int start, end;
        {
            string s1, s2;
            cin >> s1 >> s2;
            start = dict[s1];
            end = dict[s2];
        }
        int ans = -1;
        vector<vector<int> > memo(idx+1, vector<int>(24, INT_MAX));
        priority_queue<Tag> q;
        for(int i = 0; i < roads[start].size(); ++i) {
            q.push(Tag(0, roads[start][i].start, start));
        }
        while(!q.empty()) {
            const Tag tag = q.top();
            q.pop();

            if(memo[tag.pos][tag.hour] <= tag.cost) continue;
            memo[tag.pos][tag.hour] = tag.cost;

            //cout << tag.pos << endl;
            if(tag.pos == end) {
                ans = tag.cost;
                break;
            }

            for(int i = 0; i < roads[tag.pos].size(); ++i) {
                const Road &road = roads[tag.pos][i];
                int nc = tag.cost;
                //if((road.start+24-tag.hour) % 24 > 12) ++nc;
                for(int j = tag.hour; j != road.start; j = (j+1)%24) {
                    if(j == 12) ++nc;
                }
                if(memo[road.eidx][road.end] <= nc) continue;
                q.push(Tag(nc, road.end, road.eidx));
            }
        }

        cout << "Test Case " << CASE << "." << endl;
        if(ans == -1) {
            cout << "There is no route Vladimir can take." << endl;
        }
        else {
            cout << "Vladimir needs " << ans << " litre(s) of blood." << endl;
        }
    }

    return 0;
}
