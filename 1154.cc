//Name: LETTERS
//Level: 2
//Category: 深さ優先探索,やるだけ
//Note:

/*
 * DPかと思いきや、4方向に行けるので深さ優先探索で求める。
 * フラグの管理に注意。
 */
#include <iostream>
#include <string>

using namespace std;

string field[20];
bool used[26];
int R, C;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int search(int x, int y) {
    int best = 0;
    for(int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || C <= nx || ny < 0 || R <= ny) continue;

        char ch = field[ny][nx];
        if(!used[ch-'A']) {
            used[ch-'A'] = true;
            int tmp = search(nx, ny);
            if(tmp > best) best = tmp;
            used[ch-'A'] = false;
        }
    }

    return best+1;
}

int main() {
    cin >> R >> C;
    for(int i = 0; i < R; ++i) {
        cin >> field[i];
    }
    used[field[0][0]-'A'] = true;
    cout << search(0, 0) << endl;
    return 0;
}
