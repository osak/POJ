//Name: Corporative Network
//Level: 3
//Category: Union Find
//Note:

/*
 * 併合で消えるのは常にUnion Findのルートであることに注意する．
 * この性質により，ある点からServerへ行く経路は常に1つに定まる．
 *
 * Union Findの各ノードが「自分からServerまでの距離」を持つようにすると，
 * この距離は
 * 「自分から途中のノードどれかまでの距離」+「そのノードからServerまでの距離」
 * に他ならない．
 * 上の性質より，Union Findでルートを付け変えるときに距離を足していけば良いことが分かる．
 * 結合はもっと単純で，ノードiのルートをjのルートに付け変え，距離はjからServerまでの距離に
 * |i-j|%1000を加えたものになる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

//Verified PKU 2524
//Verified PKU 1522
pair<int,int> getroot(int i, vector<pair<int,int> > &roots) {
    if(roots[i].first == i) return roots[i];
    pair<int,int> parent = getroot(roots[i].first, roots);
    return roots[i] = make_pair(parent.first, parent.second+roots[i].second);
}

// roots[i] should be top
bool unite(int i, int j, vector<pair<int,int> > &roots) {
    pair<int,int> ip = getroot(i, roots);
    pair<int,int> jp = getroot(j, roots);
    if(ip.first == jp.first) return false;

    roots[i] = make_pair(jp.first, jp.second + abs(i-j)%1000);
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    scanf("%d", &T);
    while(T--) {
        int N;
        scanf("%d", &N);
        vector<pair<int,int> > roots(N+1);
        for(int i = 1; i <= N; ++i) {
            roots[i] = make_pair(i, 0);
        }
        while(true) {
            char cmd;
            scanf(" %c", &cmd);
            if(cmd == 'E') {
                int i;
                scanf("%d", &i);
                printf("%d\n", getroot(i, roots).second);
            }
            else if(cmd == 'I') {
                int i, j;
                scanf("%d %d", &i, &j);
                unite(i, j, roots);
            }
            else if(cmd == 'O') {
                break;
            }
        }
    }

    return 0;
}
