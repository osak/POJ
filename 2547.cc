//Name: No Tipping
//Level: 2
//Category: 探索,メモ化再帰,深さ優先探索,DFS
//Note:

/*
 * N<=20かつ手順の出力が必要なので，深さ優先で全探索する．
 * 枝刈りの条件は
 * ・トルクのバランスが崩れたとき
 * ・取り除いた箱の組み合わせが過去に出現していたとき
 * の二つ．
 */
#include <iostream>
#include <vector>

using namespace std;

const double LEFT_FULCRUM = -1.5;
const double RIGHT_FULCRUM = 1.5;

struct Package {
    int pos;
    int weight;

    Package() {}
    Package(int p, int w) : pos(p), weight(w) {}

    double torque(double base) const {
        return (pos-base)*weight;
    }
};

vector<int> memo(1<<20, true);
bool dfs(double left, double right, vector<int> &history, int used, const vector<Package> &packs) {
    if(memo[used]) return false;
    if(left < 0 || right > 0) return false;
    if(history.size() == packs.size()) return true;

    for(int i = 0; i < packs.size(); ++i) {
        if(used & (1<<i)) continue;
        const Package &pack = packs[i];

        double nl = left - pack.torque(LEFT_FULCRUM);
        double nr = right - pack.torque(RIGHT_FULCRUM);
        history.push_back(i);
        if(dfs(nl, nr, history, used | (1<<i), packs)) return true;
        else history.pop_back();
    }
    memo[used] = true;
    return false;
}

int main() {
    for(int CASE = 1; ; ++CASE) {
        int L, W, N;
        cin >> L >> W >> N;
        if(!L && !W && !N) break;

        memo = vector<int>(1<<20, 0);
        double left = (0-LEFT_FULCRUM)*W;
        double right = (0-RIGHT_FULCRUM)*W;
        vector<Package> packs(N);
        for(int i = 0; i < N; ++i) {
            cin >> packs[i].pos >> packs[i].weight;
            left += packs[i].torque(LEFT_FULCRUM);
            right += packs[i].torque(RIGHT_FULCRUM);
        }

        cout << "Case " << CASE << ':' << endl;
        vector<int> history;
        if(!dfs(left, right, history, 0, packs)) {
            cout << "Impossible" << endl;
        }
        else {
            for(int i = 0; i < N; ++i) {
                cout << packs[history[i]].pos << ' ' << packs[history[i]].weight << endl;
            }
        }
    }

    return 0;
}
