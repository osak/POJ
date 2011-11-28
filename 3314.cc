#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, W, B;
        cin >> N >> W >> B;
        if(!N && !W && !B) break;

        vector<int> top(W, B-1);

        vector<int> ans;
        for(int C = 0; C < N; ++C) {
            int H;
            cin >> H;
            vector<string> plaque(H);
            for(int i = 0; i < H; ++i) cin >> plaque[i];

            vector<int> pb(W, 0), pt(W, -1);
            for(int y = 0; y < H; ++y) {
                for(int x = 0; x < W; ++x) {
                    if(plaque[y][x] == 'X') pb[x] = y;
                    if(pt[x] == -1 && plaque[y][x] == 'X') pt[x] = y;
                }
            }

            int py = B-1;
            for(int x = 0; x < W; ++x) {
                py = min(py, top[x]-pb[x]);
            }
            if(py < 0) {
                ans.push_back(B-1-*min_element(top.begin(), top.end()));
                py = B - H;
            }
            for(int x = 0; x < W; ++x)
                top[x] = py + pt[x] - 1;
        }
        ans.push_back(B-1-*min_element(top.begin(), top.end()));
        for(int i = 0; i < ans.size(); ++i) {
            if(i > 0) cout << " ";
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
