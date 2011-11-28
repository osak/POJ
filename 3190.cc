#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> Interval;

struct Tag {
    int cow, t;
    bool in;

    Tag() {}
    Tag(int c, int tt, bool i) : cow(c), t(tt), in(i) {}

    bool operator < (const Tag &other) const {
        return t < other.t;
    }
};

int main() {
    int N;
    cin >> N;

    vector<Interval> v(N);
    vector<Tag> cp;
    vector<int> barn(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i].first >> v[i].second;
        cp.push_back(Tag(i, v[i].first, true));
        cp.push_back(Tag(i, v[i].second+1, false));
    }
    sort(cp.begin(), cp.end());

    int barncnt = 0;
    queue<int> q;
    for(int i = 0; i < cp.size(); ++i) {
        Tag t = cp[i];
        if(t.in) {
            if(q.empty()) {
                barn[t.cow] = ++barncnt;
            }
            else {
                barn[t.cow] = q.front();
                q.pop();
            }
            //cout << t.cow << " -> " << barn[t.cow] << endl;
        }
        else {
            q.push(barn[t.cow]);
            //cout << t.cow << " <- " << barn[t.cow] << endl;
        }
    }

    cout << barncnt << endl;
    for(int i = 0; i < N; ++i) {
        cout << barn[i] << endl;
    }
    return 0;
}
