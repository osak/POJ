#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<int> &depth, const vector<vector<int> > &edge, int pos) {
    for(int i = 0; i < edge[pos].size(); ++i) {
        if(depth[edge[pos][i]] >= 0) continue;
        depth[edge[pos][i]] = depth[pos]+1;
        dfs(depth, edge, edge[pos][i]);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<int> depth(N+1, -1);
    vector<vector<int> > edge(N+1);

    for(int i = 0; i < N-1; ++i) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    depth[N] = 0;
    dfs(depth, edge, M);

}
