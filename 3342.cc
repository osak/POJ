//Name: Party at Hali-Bula
//Level: 3
//Category: 木構造,再帰
//Note

/*
 * 一人につき、選択できる場合とできない場合両方を確かめる。
 * 曖昧性があるのは、
 * ・自分が選択可能で、選択する、しないに関わらず同じ人数になるとき
 * ・自分の子が曖昧性を持つとき
 */

#include <iostream>
#include <map>
#include <vector>
#include <map>
#include <queue>

#define FOREACH(V, E) for(__typeof(E.begin()) V = E.begin(); V != E.end(); ++V)

using namespace std;

pair<int, bool> dfs(const vector<vector<int> > &hier, int pos, bool canselect) {
    int ret_res = 0;
    bool ret_dup = 0;
    if(canselect) {
        int res = 1;
        bool dup = false;
        FOREACH(i, hier[pos]) {
            pair<int, bool> ret = dfs(hier, *i, false);
            res += ret.first;
            dup |= ret.second;
        }
        ret_res = res;
        ret_dup = dup;
    }
    {
        int res = 0;
        bool dup = false;
        FOREACH(i, hier[pos]) {
            pair<int, bool> ret = dfs(hier, *i, true);
            res += ret.first;
            dup |= ret.second;
        }
        if(ret_res == res) ret_dup = true;
        else {
            if(ret_res < res) {
                ret_res = res;
                ret_dup = dup;
            }
        }
    }

    return make_pair(ret_res, ret_dup);
}


int main() {
    while(true) {
        while(true) {
            int N;
            cin >> N;
            if(!N) return 0;

            vector<vector<int> > hier(N);
            vector<int> boss(N, -1);
            map<string, int> dict;
            int seq = 0;

            string top;
            cin >> top;
            dict[top] = seq++;
            for(int i = 1; i < N; ++i) {
                string name, bossname;
                cin >> name >> bossname;
                if(dict.count(name) <= 0) dict[name] = seq++;
                if(dict.count(bossname) <= 0) dict[bossname] = seq++;

                hier[dict[bossname]].push_back(dict[name]);
                boss[dict[name]] = dict[bossname];
            }

            pair<int, bool> res = dfs(hier, 0, true);
            cout << res.first << " " << (res.second?"No":"Yes") << endl;
        }
    }
    return 0;
}
