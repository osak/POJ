#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int orgR, orgC;
char T;
vector<string> field(8);
vector<string> ans;

int sign(int n) {
    if(n == 0) return 0;
    return n<0 ? -1 : 1;
}

void check(int dR, int dC) {
    if(dR == 0 && dC == 0) return;
    int dr = 0, dc = 0;
    bool ok = true;
    do {
        dr += sign(dR);
        dc += sign(dC);
        int r = orgR + dr;
        int c = orgC + dc;
        if(0 <= r && r < 8 && 0 <= c && c < 8 && (field[r][c] == '.' || field[r][c] == T)) {}
        else {
            ok = false;
            break;
        }
    } while(dr != dR || dc != dC);
    if(ok && field[orgR+dR][orgC+dC] == '.') {
        ostringstream os;
        os << (char)('A'+orgR) << (orgC+1) << "-" << (char)('A'+orgR+dR) << (orgC+dC+1);
        ans.push_back(os.str());
    }
}

int main() {
    while(cin >> field[0]) {
        for(int i = 1; i < 8; ++i) cin >> field[i];
        cin >> T;

        ans.clear();
        for(int R = 0; R < 8; ++R) {
            for(int C = 0; C < 8; ++C) {
                if(field[R][C] != T) continue;

                //piece count on row
                int pr = 0;
                for(int c = 0; c < 8; ++c)
                    if(field[R][c] != '.') ++pr;

                //piece count on column
                int pc = 0;
                for(int r = 0; r < 8; ++r)
                    if(field[r][C] != '.') ++pc;

                //piece count on upright-downleft
                int pur = 0;
                for(int r = 0; r < 8; ++r) {
                    int c = R+C-r;
                    if(0 <= c && c < 8 && field[r][c] != '.') ++pur;
                }

                //piece count on upleft-downright
                int pul = 0;
                for(int r = 0; r < 8; ++r) {
                    int c = C+r-R;
                    if(0 <= c && c < 8 && field[r][c] != '.') ++pul;
                }
                orgR = R;
                orgC = C;
                check(R-pul, C-pul) ; check(R-pc, C) ; check(R-pur, C+pur) ;
                check(R, C-pr)      ;                  check(R, C+pr)      ;
                check(R+pur, C-pur) ; check(R+pc, C) ; check(R+pul, C+pul);
            }
        }
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); ++i) cout << ans[i] << endl;
    }
    return 0;
}
