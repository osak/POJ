//Name: Chutes and Ladders
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

/*
 * アメリカで有名なすごろくゲーム。
 * 問題の通りにシミュレーションすればよい。
 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    vector<int> dice;
    while(true) {
        int n;
        cin >> n;
        if(!n) break;
        dice.push_back(n);
    }

    while(true) {
        int players;
        cin >> players;
        if(!players) break;

        vector<int> events(101, 0);
        map<int, int> warps;
        while(true) {
            int a, b;
            cin >> a >> b;
            if(!a && !b) break;
            warps[a] = b;
        }
        while(true) {
            int n;
            cin >> n;
            if(!n) break;
            if(n < 0) events[-n] = -1;
            else events[n] = 1;
        }

        vector<bool> skip(players, false);
        vector<int> pos(players, 0);
        int cur = 0;
        for(int i = 0; i < dice.size(); ++i) {
            if(skip[cur]) {
                skip[cur] = false;
                continue;
            }
            if(pos[cur] + dice[i] == 100) break;
            if(pos[cur] + dice[i] < 100) {
                pos[cur] += dice[i];
                if(warps[pos[cur]]) pos[cur] = warps[pos[cur]];
                else if(events[pos[cur]]) {
                    if(events[pos[cur]] == -1) skip[cur] = true;
                    else continue;
                }
            }
            cur = (cur+1) % players;
        }

        cout << cur+1 << endl;
    }
    return 0;
}
