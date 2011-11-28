//Name: Sea Battle
//Level: 2
//Category: シミュレーション
//Note:

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

bool isHash(const vector<string> &field, int r, int c) {
    const int R = field.size();
    const int C = field[0].size();
    if(r < 0 || R <= r || c < 0 || C <= c) return false;
    return field[r][c] == '#';
}

bool isShip(const vector<string> &field, int r, int c) {
    const int R = field.size();
    const int C = field[0].size();
    if(r < 0 || R <= r || c < 0 || C <= c) return false;
    return field[r][c] != '.';
}

int main() {
    int R, C;
    char buf[1002];
    while(true) {
        scanf(" %d %d ", &R, &C);
        if(!R && !C) break;

        vector<string> field(R);
        for(int i = 0; i < R; ++i) {
            fgets(buf, 1002, stdin);
            buf[C] = '\0';
            field[i] = string(buf);
        }

        int ans = 0;
        bool bad = false;
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(field[r][c] == '#') {
                    //Search mode
                    
                    //Determine width
                    int w = 0;
                    while(isHash(field, r, c+w)) {
                        field[r][c+w] = '.';
                        ++w;
                    }

                    //Check for rows
                    int h = 1;
                    while(isHash(field, r+h, c)) {
                        //Check for rectangleness
                        for(int offc = 0; offc < w; ++offc) {
                            if(!isHash(field, r+h, c+offc)) {
                                bad = true;
                                goto end;
                            }
                            field[r+h][c+offc] = '$';
                        }
                        if(isShip(field, r+h, c-1) || isShip(field, r+h, c+w)) {
                            bad = true;
                            goto end;
                        }
                        ++h;
                    }
                    
                    //Check if next row is empty
                    for(int offc = -1; offc <= w; ++offc) {
                        if(isShip(field, r+h, c+offc)) {
                            bad = true;
                            goto end;
                        }
                    }

                    ++ans;
                }
            }
        }
end:
        if(bad) cout << "Bad placement." << endl;
        else cout << "There are " << ans << " ships." << endl;
    }

    return 0;
}
