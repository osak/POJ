//Name: Robot
//Level: 3
//Category: 幅優先探索,迷路
//Note:

/*
 * マス目が与えられるが、動くのは線上という変わった問題。
 * ロボットの大きさが与えられているが、円形なので、
 * 結局侵入できないのは壁のあるマスの角だけになる。
 * それさえ分かれば、ロボットの状態と位置に関して幅優先探索すればよい。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

struct State {
    int x, y, dir, step;
    State() {}
    State(int xx, int yy, int dd, int ss) : x(xx), y(yy), dir(dd), step(ss) {}
};

int main() {
    while(true) {
        int M, N;
        cin >> M >> N;
        if(M == 0) break;

        vector<vector<int> > field;
        field.resize(M);
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                int tmp;
                cin >> tmp;
                field[i].push_back(tmp);
            }
        }

        int fromx, fromy, tox, toy, dir;
        string initdir;
        cin >> fromy >> fromx >> toy >> tox >> initdir;

        if(initdir == "north") dir = 0;
        else if(initdir == "east") dir = 1;
        else if(initdir == "south") dir = 2;
        else dir = 3;

        vector<vector<bool> > passable;
        passable.resize(N+1);
        for(int i = 0; i <= N; ++i) {
            passable[i].resize(M+1);
            fill(passable[i].begin(), passable[i].end(), false);
        }

        for(int y = 1; y < M; ++y) {
            for(int x = 1; x < N; ++x) {
                if(field[y-1][x-1] || field[y][x-1] || field[y-1][x] || field[y][x]) continue;
                passable[x][y] = true;
            }
        }

        vector<vector<vector<bool> > > visited(N, vector<vector<bool> >(M, vector<bool>(4, false)));
        queue<State> q;
        q.push(State(fromx, fromy, dir, 0));
        visited[fromx][fromy][dir] = true;
        int ans = -1;
        while(!q.empty()) {
            State s = q.front();
            q.pop();
            if(s.x == tox && s.y == toy) {
                ans = s.step;
                break;
            }

            int dx[] = {0, 1, 0, -1};
            int dy[] = {-1, 0, 1, 0};

            //Add straight go pattern
            for(int i = 1; i <= 3; ++i) {
                int nx = s.x + dx[s.dir]*i;
                int ny = s.y + dy[s.dir]*i;
                for(int j = 1; j <= i; ++j) {
                    if(!passable[s.x+dx[s.dir]*j][s.y+dy[s.dir]*j]) goto nextparam;
                }
                if(visited[nx][ny][s.dir]) continue;
                visited[nx][ny][s.dir] = true;
                q.push(State(nx, ny, s.dir, s.step+1));
nextparam:
                ;
            }

            //Add turn pattern
            if(!visited[s.x][s.y][(s.dir+1)%4]) {
                q.push(State(s.x, s.y, (s.dir+1)%4, s.step+1));
                visited[s.x][s.y][(s.dir+1)%4] = true;
            }
            if(!visited[s.x][s.y][(s.dir+4-1)%4]) {
                q.push(State(s.x, s.y, (s.dir+4-1)%4, s.step+1));
                visited[s.x][s.y][(s.dir+4-1)%4] = true;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
