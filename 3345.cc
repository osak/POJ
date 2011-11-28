//Name: Bribing FIPA
//Level: 4
//Category: 木構造,動的計画法,DP
//Note:

/*
 * 木構造を作ったあと、それぞれのノードごとに
 * 「自分をrootとするsubtreeからn個選ぶときの最小コスト」でDP配列を作る。
 * rootのDP配列は、子のDP配列を使ってDPすることで得られる。
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

int dfs(vector<vector<int> > &dp, const vector<vector<int> > &children, const vector<int> &cost, int node) {
    int sum = 1;
    for(int i = 0; i < children[node].size(); ++i) {
        sum += dfs(dp, children, cost, children[node][i]);
    }

    dp[node][0] = 0;
    dp[node][sum] = cost[node];
    for(int i = 0; i < children[node].size(); ++i) {
        for(int sel = sum; sel >= 0; --sel) {
            for(int cm = 0; cm <= sel; ++cm) {
                dp[node][sel] = min(dp[node][sel], dp[node][sel-cm] + dp[children[node][i]][cm]);
            }
        }
    }
    return sum;
}

int main() {
    int N, M;
    while(cin >> N >> M) {
        vector<int> parent(N+1, -1);
        vector<int> cost(N+1);
        vector<vector<int> > children(N+1);

        map<string, int> dict;
        int seq = 0;
        {
            string dmy;
            getline(cin, dmy);
        }
        for(int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);
            istringstream is(line);

            string ctr;
            int c;
            is >> ctr >> c;
            int idx = dict.count(ctr)>0 ? dict[ctr] : dict[ctr]=seq++;
            cost[idx] = c;
            while(!is.eof()) {
                string child;
                is >> child;
                if(child.size() == 0) break;
                int cidx = dict.count(child)>0 ? dict[child] : dict[child]=seq++;
                parent[cidx] = idx;
                children[idx].push_back(cidx);
            }
        }
        
        //Add super root
        cost[N] = INT_MAX/2;
        for(int i = 0; i < N; ++i) {
            if(parent[i] == -1) {
                parent[i] = N;
                children[N].push_back(i);
            }
        }

        vector<vector<int> > dp(N+1, vector<int>(N+2, INT_MAX/2));
        dfs(dp, children, cost, N);
        
        int mincost = INT_MAX;
        for(int i = M; i <= N; ++i) {
            mincost = min(mincost, dp[N][i]);
        }
        cout << mincost << endl;
    }
    return 0;
}
