#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Tag {
    int start, end;
    vector<int> hall;
    vector<int> neighbor;

    bool operator < (const Tag & other) const {
        if(start != other.start) return start < other.start;
        return end < other.end;
    }
};

int main() {
    int C;
    cin >> C;
    while(C--) {
        int N;
        cin >> N;
        
        vector<Tag> tag;

        for(int i = 0; i < N; ++i) {
            int a, b, k;
            Tag t;
            cin >> a >> b >> k;
            t.start = a;
            t.end = b;
            for(int j = 0; j < k; ++j) {
                int h;
                cin >> h;
                h--;
                t.hall.push_back(h);
            }
        }
        sort(tag.begin(), tag.end());

        for(int i = 0; i < tag.size(); ++i) {
            for(int j = i+1; j < tag.size(); ++j) {
                if(tag[i].start <= tag[j].start && tag[j].start <= tag[i].end) {
                    tag[i].neighbor.push_back(j);
                }
            }
        }

        vector<int> flag(N);
        queue<pair<int, int> > q;
        q.push(make_pair(0, 0));

        while(!q.empty()) {
            int p = q.front().first;
            int mask = q.front().second;
            q.pop();

            for(int i = 0; i < tag[p].neighbor.size(); ++i) {
                for(int j = 0; j < tag[p].hall.size(); ++j) {
                    if(mask & (1<<tag[p].hall[j])) continue;
                    q.push(make_pair(tag[p].neighbor[i], mask | (1<<tag[p].hall[j])));
                }
            }
        }
    }
}
