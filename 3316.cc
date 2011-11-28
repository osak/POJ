#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

inline bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

bool paint(vector<string> &v, vector<pair<int, int> > &term, int x, int y) {
    const int H = v.size();
    const int W = v[0].size();

    v[y][x] = '2';
    int nc = 0;
    bool ok = true;
    for(int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if(!inRange(0, xx, W-1) || !inRange(0, yy, H-1)) continue;
        if(v[yy][xx] != '0') ++nc;
        if(v[yy][xx] == '1') {
            if(!paint(v, term, xx, yy)) ok = false;
        }
    }
    if(nc <= 1) term.push_back(make_pair(x, y));

    return ok && nc <= 2;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<string> v(N);
        vector<vector<bool> > used(N, vector<bool>(M, false));

        for(int i = 0; i < N; ++i)
            cin >> v[i];

        int ans = 0;
        for(int y = 0; y < N; ++y) {
            for(int x = 0; x < M; ++x) {
                if(v[y][x] == '1') {
                    vector<pair<int, int> > term; 
                    bool isMaximal = true;
                    if(!paint(v, term, x, y)) {
                        isMaximal = false;
                        goto end;
                    }

                    for(int i = 0; i < term.size(); ++i) {
                        //cout << "Term " << term[i].first << ' ' << term[i].second << endl;
                        for(int j = 0; j < 4; ++j) {
                            int xx = term[i].first + dx[j];
                            int yy = term[i].second + dy[j];
                            if(!inRange(0, xx, M-1) || !inRange(0, yy, N-1)) continue;
                            if(v[yy][xx] != '0') continue;
                            //cout << xx << ' ' << yy << "checking..." << endl;

                            bool ok = false;
                            for(int k = 0; k < 4; ++k) {
                                int xxx = xx + dx[k];
                                int yyy = yy + dy[k];
                                if(!inRange(0, xxx, M-1) || !inRange(0, yyy, N-1)) continue;
                                if(yyy == term[i].second && xxx == term[i].first) continue;
                                //if(term[0].first == xxx && term[0].second == yyy) continue;
                                //if(term[1].first == xxx && term[1].second == yyy) continue;
                                //cout << xxx << ' ' << yyy << "checked" << endl;
                                if(v[yyy][xxx] != '0') {
                                    ok = true;
                                    break;
                                }
                            }
                            if(!ok) {
                                //cout << "NG" << endl;
                                isMaximal = false;
                                goto end;
                            }
                        }
                    }
end:
                    if(isMaximal) ++ans;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
