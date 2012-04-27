//Name: K Best
//Level: 4
//Category: 数学,二分探索,Special Judge
//Note:

/*
 * あるxに対してs(S) ≧ xを満たす選び方があるかを考えると，xの二分探索に帰着できる．
 * s(S) ≧ xは変形すると
 * Σv_i ≧ xΣw_i
 * Σv_i - xΣw_i ≧ 0
 * Σ(v_i - xw_i) ≧ 0
 * となるから，v_i-xw_iでソートして大きい方からK個取ることで判定可能．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Jewel {
    int v, w;
    int idx;
};

struct Cmp {
    double x;

    Cmp(double x) : x(x) {}
    bool operator ()(const Jewel &a, const Jewel &b) const {
        return a.v-x*a.w < b.v-x*b.w;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;
    vector<Jewel> jewels(N);
    for(int i = 0; i < N; ++i) {
        cin >> jewels[i].v >> jewels[i].w;
        jewels[i].idx = i+1;
    }
    double left = 0, right = 1e7;
    for(int step = 0; step < 100; ++step) {
        double center = (left+right)/2;
        sort(jewels.begin(), jewels.end(), Cmp(center));

        double sum = 0;
        for(int i = N-K; i < N; ++i) {
            sum += jewels[i].v - center*jewels[i].w;
        }
        if(sum > 0) {
            left = center;
        }
        else {
            right = center;
        }
    }

    for(int i = N-K; i < N; ++i) {
        if(i > N-K) cout << ' ';
        cout << jewels[i].idx;
    }
    cout << endl;
    return 0;
}
