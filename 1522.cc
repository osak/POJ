//Name: N-Credible Mazes
//Level: 2
//Category: やるだけ,Union Find
//Note:

/*
 * ベクトルに通し番号を振って，Union Findで結合していくだけ．
 * ベクトルがいくつ来るか分からないので，動的に伸ばせるようにする．
 * (最初にinputを全部読んでしまっても良いと思う)
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

//Verified PKU 2524
int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}

map<vector<int>,int> dict;
int readpos(int N) {
    vector<int> v(N);
    cin >> v[0];
    if(v[0] == -1) return -1;

    for(int i = 1; i < N; ++i) {
        cin >> v[i];
    }
    if(dict.count(v)) return dict[v];
    return dict[v] = dict.size();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int CASE = 1; ; ++CASE) {
        int N;
        cin >> N;
        if(!N) break;
        dict.clear();

        int start = readpos(N);
        int goal = readpos(N);
        vector<int> roots(100), levels(100, 0);
        for(int i = 0; i < 100; ++i) {
            roots[i] = i;
        }

        while(true) {
            int p = readpos(N);
            if(p == -1) break;
            int q = readpos(N);

            int mx = max(p, q);
            if((int)roots.size() <= mx) {
                for(int i = roots.size(); i <= mx; ++i) {
                    roots.push_back(i);
                    levels.push_back(0);
                }
            }
            unite(p, q, roots, levels);
        }

        cout << "Maze #" << CASE;
        if(getroot(start, roots) == getroot(goal, roots)) {
            cout << " can be travelled" << endl;
        }
        else {
            cout << " cannot be travelled" << endl;
        }
    }

    return 0;
}
