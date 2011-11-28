#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<vector<int> > v(N+1, vector<int>(N+1, INT_MAX/2));

        for(int i = 0; i < N+1; ++i)
            for(int j = 0; j < N+1; ++j)
                cin >> v[i][j];

        for(int k = 0; k < N+1; ++k)
            for(int i = 0; i < N+1; ++i)
                for(int j = 0; j < N+1; ++j)
                    v[i][j] = min(v[i][j], v[i][k]+v[k][j]);

        vector<int> order;
        for(int i = 1; i < N+1; ++i) order.push_back(i);

        int ans = INT_MAX;
        do {
            int total = 0;
            int prev = 0;
            for(int i = 0; i < order.size(); ++i) {
                total += v[prev][order[i]];
                prev = order[i];
            }
            total += v[prev][0];
            ans = min(ans, total);
        } while(next_permutation(order.begin(), order.end()));

        cout << ans << endl;
    }
    return 0;
}
