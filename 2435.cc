//Name: Navigating the City
//Level: 2
//Category: グラフ,最短距離,経路復元,幅優先探索,BFS
//Note:

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;

const int INF = 40*30*10;
const string DD = "NESW";
const int DR[] = {-1, 0, 1, 0};
const int DC[] = {0, 1, 0, -1};

struct Tag {
    pair<int,int> pos;
    int cost;

    Tag() {}
    Tag(const pair<int,int> &p, int c) : pos(p), cost(c) {}
};

int main() {
    int N, E;
    cin >> N >> E;
    int R = 2*N-1, C = 2*E-1;

    vector<string> field(R);
    pair<int,int> S, G;
    for(int i = 0; i < R; ++i) {
        cin >> field[i];
        for(int j = 0; j < C; ++j) {
            if(field[i][j] == 'S') S = make_pair(i, j);
            if(field[i][j] == 'E') G = make_pair(i, j);
        }
    }

    vector<vector<int> > prev(R, vector<int>(C, -1));
    vector<vector<int> > cost(R, vector<int>(C, INF));
    queue<Tag> q;
    q.push(Tag(S, 0));
    cost[S.first][S.second] = 0;
    while(!q.empty()) {
        const Tag t = q.front();
        q.pop();

        //cout << t.pos.first << ' ' << t.pos.second << endl;
        if(field[t.pos.first][t.pos.second] == 'E') {
            break;
        }

        for(int i = 0; i < 4; ++i) {
            int nr = t.pos.first + DR[i];
            int nc = t.pos.second + DC[i];
            char dir = DD[i];
            if(nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
            if(field[nr][nc] == '.') continue;

            nr += DR[i];
            nc += DC[i];
            if(cost[nr][nc] != INF) continue;
            cost[nr][nc] = t.cost+1;
            prev[nr][nc] = (i+2)%4;
            q.push(Tag(make_pair(nr, nc), t.cost+1));
        }
    }

    vector<pair<char,int> > seq;
    pair<int,int> cur = G;
    while(cur != S) {
        int p = prev[cur.first][cur.second];
        char dir = DD[(p+2)%4];
        pair<int,int> next = make_pair(cur.first+DR[p]*2, cur.second+DC[p]*2);
        if(seq.size() > 0 && seq.back().first == dir) seq.back().second++;
        else seq.push_back(make_pair(dir, 1));

        cur = next;
    }

    for(int i = seq.size()-1; i >= 0; --i) {
        cout << seq[i].first << ' ' << seq[i].second << endl;
    }

    return 0;
}
