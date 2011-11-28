#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int pos, vector<int> &maxrem, vector<int> &used, const vector<vector<int> > &v, int N) {
    used[pos] = true;
    maxrem[pos] = 0;
    int sum = 0;
    for(int i = 0; i < v[pos].size(); ++i) {
        if(used[v[pos][i]]) continue;
        int val = dfs(v[pos][i], maxrem, used, v, N);
        sum += val;
        maxrem[pos] = max(maxrem[pos], val);
    }
    maxrem[pos] = max(maxrem[pos], N-sum-1);
    
    return sum+1;
}

int main() {
    int N;
    scanf("%d", &N);

    vector<vector<int> > v(N+1);
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }

    vector<int> maxrem(N+1, 0);
    vector<int> used(N+1, 0);
    int minval = N+1;
    dfs(1, maxrem, used, v, N);
    for(int i = 1; i <= N; ++i)
        minval = min(minval, maxrem[i]);
    bool first = true;
    for(int i = 1; i <= N; ++i) {
        if(minval == maxrem[i]) {
            if(!first) printf(" ");
            printf("%d", i);
            first = false;
        }
    }
    puts("");

    return 0;
}
