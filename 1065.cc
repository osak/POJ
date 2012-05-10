//Name: Wooden Sticks
//Level: 3
//Category: DAG,最小パス被覆,Minimum path cover
//Note:

/*
 * 3636 Nested Dollsとほぼ同じ．
 * (参照: https://github.com/osak/POJ/blob/master/3636.cc)
 * ただし条件に等号が入っているため，同じfirstをまとめて処理する必要はない．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    scanf("%d", &T);
    while(T--) {
        int N;
        scanf("%d", &N);

        vector<pair<int, int> > sticks(N);
        for(int i = 0; i < N; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            sticks[i].first = a;
            sticks[i].second = b;
        }
        sort(sticks.begin(), sticks.end());
        sticks.erase(unique(sticks.begin(), sticks.end()), sticks.end());

        multiset<int> ws;
        vector<pair<int,int> >::iterator it = sticks.begin(); 
        while(it != sticks.end()) {
            multiset<int>::iterator ub = ws.upper_bound(it->second);
            if(ub != ws.begin()) {
                --ub;
                ws.erase(ub);
            }
            ws.insert(it->second);
            ++it;
        }

        cout << ws.size() << endl;
    }

    return 0;
}
