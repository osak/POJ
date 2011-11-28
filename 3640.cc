#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>

typedef long long LL;

using namespace std;

struct Tag {
    int n;
    vector<int> v;
};

int main() {
    while(true) {
        int N;
        scanf("%d", &N);
        if(!N) break;

        map<LL,int> m;
        for(int i = 0; i < N; ++i) {
            int ns[5];
            LL hash = 0;
            scanf("%d %d %d %d %d", ns, ns+1, ns+2, ns+3, ns+4);
            sort(ns, ns+5);
            for(int j = 0; j < 5; ++j) {
                hash *= 100;
                hash += ns[j];
            }
            m[hash]++;
        }

        int ans = 0;
        int cnt = 0;
        for(map<LL,int>::iterator it = m.begin(); it != m.end(); ++it) {
            if(ans == it->second) ++cnt;
            else if(ans < it->second) {
                ans = it->second;
                cnt = 1;
            }
        }
        printf("%d\n", ans*cnt);
    }
    return 0;
}
