//Name: Tour de France
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int N, M;
        cin >> N;
        if(!N) break;
        cin >> M;

        vector<int> ns(N), ms(M);
        for(int i = 0; i < N; ++i) cin >> ns[i];
        for(int i = 0; i < M; ++i) cin >> ms[i];

        vector<double> ratio;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                ratio.push_back((double)ns[i] / ms[j]);
            }
        }
        sort(ratio.begin(), ratio.end());

        double ans = 0;
        for(int i = 1; i < ratio.size(); ++i)
            ans = max(ans, ratio[i] / ratio[i-1]);

        printf("%.2f\n", ans);
    }
    return 0;
}
