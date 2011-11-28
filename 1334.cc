#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> heights(N);
        for(int i = 0; i < N; ++i) {
            int x;
            cin >> x >> heights[i];
        }
        int ans = 0;
        int a = 0, b = N-1;
        int level = heights[a];
        int next = min(heights[a+1], heights[b-1]);

        while(a != N-1 && b != 0) {
            int na, nb;
            int fa, fb;
            na = (level == heights[a]) ? heights[a+1] : heights[a];
            nb = (level == heights[b]) ? heights[b-1] : heights[b];
            fa = level-na > 0 ? 1 : -1;
            fb = level-nb > 0 ? 1 : -1;
            if(fa == fb) {
                level = min(na, nb);
                if(heights[a+1] == na) a++;
                if(heights[b-1] == nb) b--;
            }
            else {

        }
}
