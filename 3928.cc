//Name: Ping pong
//Level: 3
//Category: セグメント木,Segtree
//Note: セグメント木のデバッグに便利

/*
 * 単調増加 or 単調減少なsubsequenceの個数を数えればよい．
 * a_iより左にある点のうち，a_iより大きいものの個数をhigh[i], 小さいものの個数をlow[i]とすると
 * あるa_iが追加されたとき，これを右の端点とするsubsequenceの数は
 * ・a_iより大きい数a_jにおけるhigh[j]の和
 * ・a_iより小さい数a_jにおけるlow[j]の和
 * で計算できる．
 * 普通にやるとO(N^2)だが，highとlowをそれぞれ平方分割して管理すると上の総和が高速に求められる．
 * また，high, lowの更新自体にも同様の平方分割木が使える．
 */
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ULL;
//typedef unsigned int ULL;

const int MAXN = 20165;
const int SEGSIZE = 142; // sqrt(MAXN)
//const int MAXN = 100001;
//const int SEGSIZE = 317; // sqrt(MAXN)
struct Segtree {
    vector<ULL> segsum, raw;

    Segtree() : segsum(SEGSIZE, 0), raw(MAXN, 0) {}

    void insert(int idx, ULL val) {
        segsum[idx/SEGSIZE] -= raw[idx];
        raw[idx] = val;
        segsum[idx/SEGSIZE] += val;
    }

    ULL getval(int idx) const {
        return raw[idx];
    }

    // sum of [start, end)
    ULL getsum(int start, int end) const {
        int si = start/SEGSIZE;
        if(start % SEGSIZE > 0) si++;
        int ei = end/SEGSIZE;
        if(end % SEGSIZE == SEGSIZE-1) ei++;

        ULL res = 0;
        for(int i = si; i < ei; ++i) {
            res += segsum[i];
        }
        for(int i = start; i < si*SEGSIZE; ++i) {
            res += raw[i];
        }
        for(int i = ei*SEGSIZE; i < end; ++i) {
            res += raw[i];
        }
        return res;
    }

    void clear() {
        fill(segsum.begin(), segsum.end(), 0);
        fill(raw.begin(), raw.end(), 0);
    }
};

vector<int> as;
int mapping[1000001];
Segtree low, high, cnt;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int N;
        scanf("%d", &N);

        as.clear();
        memset(mapping, 0, sizeof(mapping));
        low.clear();
        high.clear();
        cnt.clear();
        for(int i = 0; i < N; ++i) {
            int a;
            scanf("%d", &a);
            as.push_back(a);
            mapping[a] = 1;
        }

        int idx = 1;
        for(int i = 0; i < 100001; ++i) {
            if(mapping[i]) mapping[i] = idx++;
        }

        ULL ans = 0;
        for(vector<int>::iterator it = as.begin(); it != as.end(); ++it) {
            int a = mapping[*it];
            int diff = it - as.begin();
            ans += low.getsum(0, a);
            ans += high.getsum(a+1, MAXN);

            ULL lc = cnt.getsum(0, a);
            low.insert(a, lc);
            high.insert(a, diff-lc);
            cnt.insert(a, 1);
        }
        cout << ans << endl;
    }

    return 0;
}
