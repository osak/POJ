//Name: The Umbrella Problem: 2054
//Level: 2
//Category: シミュレーション
//Note:

/*
 * BFSなりDPなりで適当にやるだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cctype>

using namespace std;

bool safe(int turn, int col, char c, const vector<pair<int,int> > &guns) {
    if(c == 'S' || c == 'P') return false;
    int checkdir = (1<<(turn%4)) | (1<<((turn+3)%4));
    for(vector<pair<int,int> >::const_iterator it = guns.begin(); it != guns.end(); ++it) {
        if(checkdir & 0x01) { // up
            if(col == it->second && turn < it->first) return false;
        }
        if(checkdir & 0x02) { // right
            if(col > it->second && turn == it->first) return false;
        }
        if(checkdir & 0x04) { // down
            if(col == it->second && turn > it->first) return false;
        }
        if(checkdir & 0x08) { // left
            if(col < it->second && turn == it->first) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string cmd;
        cin >> cmd;
        if(cmd == "ENDOFINPUT") break;

        int C, R;
        cin >> C >> R;
        vector<string> v(R);
        vector<pair<int,int> > guns;
        for(int i = 0; i < R; ++i) {
            cin >> v[i];
            for(int j = 0; j < C; ++j) {
                if(v[i][j] == 'L') {
                    v[i][j] = 'l';
                }
                else if(v[i][j] == 'S') {
                    guns.push_back(make_pair(i, j));
                }
            }
        }
        cin >> cmd; // ignore "END"

        for(vector<pair<int,int> >::const_iterator it = guns.begin(); it != guns.end(); ++it) {
            v[0][it->second] = toupper(v[0][it->second]);
        }
        for(int r = 0; r < R-1; ++r) {
            //cout << v[r] << endl;
            for(int c = 0; c < C; ++c) {
                if(islower(v[r][c])) {
                    if(c-1 >= 0 && safe(r+1, c-1, v[r+1][c-1], guns)) {
                        v[r+1][c-1] = tolower(v[r+1][c-1]);
                    }
                    if(safe(r+1, c, v[r+1][c], guns)) {
                        v[r+1][c] = tolower(v[r+1][c]);
                    }
                    if(c+1 < C && safe(r+1, c+1, v[r+1][c+1], guns)) {
                        v[r+1][c+1] = tolower(v[r+1][c+1]);
                    }
                }
            }
        }

        bool can = false;
        for(int c = 0; c < C; ++c) {
            if(v[R-1][c] == 'g') can = true;
        }

        cout << (can?"FERRET":"GARRET") << endl;
    }

    return 0;
}
