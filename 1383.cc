#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

struct Tag {
    int r, c, dist;
    Tag() {}
    Tag(int r, int c, int d) : r(r), c(c), dist(d) {}
};

char field[1000][1002];
int dist[1000][1002];
int R, C;

bool is(int r, int c, char ch) {
    if(r < 0 || R <= r || c < 0 || C <= c) return false;
    return field[r][c] == ch;
}

Tag fill(int r, int c) {
    static int dc[] = {1, 0, -1, 0};
    static int dr[] = {0, -1, 0, 1};

    Tag mv(-1, -1, -1);
    queue<Tag> q;
    q.push(Tag(r, c, 0));
    while(!q.empty()) {
        const Tag &t = q.front();
        q.pop();

        //printf("%d %d %d\n", t.r, t.c, t.dist);
        if(t.dist > mv.dist) mv = t;
        dist[t.r][t.c] = t.dist;
        for(int i = 0; i < 4; ++i) {
            int nr = t.r + dr[i];
            int nc = t.c + dc[i];
            if(is(nr, nc, '.') && dist[nr][nc] == -1) q.push(Tag(nr, nc, t.dist+1));
        }
    }

    return mv;
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) {
        scanf(" %d %d ", &C, &R);
        for(int i = 0; i < R; ++i) {
            fgets(field[i], 1001, stdin);
            field[i][C] = '\0';
        }

        Tag mv(0, 0, 0);
        memset(dist, -1, sizeof(dist));
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(is(r, c, '.')) {
                    mv = fill(r, c);
                    goto next;
                }
            }
        }

next:
        memset(dist, -1, sizeof(dist));
        mv = fill(mv.r, mv.c);
        printf("Maximum rope length is %d.\n", mv.dist);
    }

    return 0;
}
