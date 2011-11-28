#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

struct Tag {
    int pos, state, turn;

    int hash() const { return (pos<<12) + state; }

    Tag() {}
    Tag(int p, int s, int t) : pos(p), state(s), turn(t) {}
    Tag(int h) : pos(h>>12), state(h&0x7ff) {}
};

int bitpos(int n) {
    int p = 0;
    while(!(n&1)) {
        ++p;
        n >>= 1;
    }
    return p;
}

int main() {
    for(int C = 1; ; C++) {
        int R, D, S;
        cin >> R >> D >> S;
        if(!R && !D && !S) break;

        int v[R][R];
        memset(v, 0, sizeof(v));

        vector<vector<int> > l(R);
        for(int i = 0; i < D; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            v[a][b] = v[b][a] = 1;
        }
        for(int i = 0; i < S; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if(a != b) l[a].push_back(b);
        }

        int hist[R][1<<(R+1)];
        memset(hist, 0, sizeof(hist));
        bool found = false;
        vector<string> ans;
        queue<Tag> q;
        q.push(Tag(0, 1, 0));
        while(!q.empty()) {
            Tag t = q.front();
            q.pop();

            if(t.pos == R-1 && t.state == (1<<(R-1))) {
                found = true;
                while(t.pos != 0 || t.state != 1) {
                    Tag prev(hist[t.pos][t.state]);
                    ostringstream os;

                    if(t.pos != prev.pos) {
                        os << "- Move to room " << (t.pos+1) << ".";
                    }
                    else {
                        int mask = t.state ^ prev.state;
                        if(t.state & mask) {
                            os << "- Switch on light in room " << (bitpos(mask)+1) << ".";
                        }
                        else {
                            os << "- Switch off light in room " << (bitpos(mask)+1) << ".";
                        }
                    }
                    t = prev;
                    ans.push_back(os.str());
                }
                break;
            }

            //move
            for(int i = 0; i < R; ++i) {
                if(!v[t.pos][i]) continue;
                if(hist[i][t.state]) continue;
                if(!(t.state & (1<<i))) continue;

                hist[i][t.state] = t.hash();
                q.push(Tag(i, t.state, t.turn+1));
            }

            //light
            for(int i = 0; i < l[t.pos].size(); ++i) {
                int ns = t.state ^ (1<<l[t.pos][i]);
                if(hist[t.pos][ns]) continue;

                hist[t.pos][ns] = t.hash();
                q.push(Tag(t.pos, ns, t.turn+1));
            }
        }
        cout << "Villa #" << C << endl;
        if(!found) {
            cout << "The problem cannot be solved." << endl;
        }
        else {
            cout << "The problem can be solved in " << ans.size() << " steps:" << endl;
            for(int i = ans.size()-1; i >= 0; --i) {
                cout << ans[i] << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
