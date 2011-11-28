//Name: Product
//Level: 2
//Category: パターン分け
//Note:

/*
 * 基本的には絶対値の大きい方から取っていけばよい．
 * ただし，これで全体の積が負になるときは調整が必要で，
 * …答えの中にある正数を除いて負数を加える
 * …答えの中にある負数を除いて正数を加える
 * のどちらかを選び，大きいほうを選ぶ．
 * どうしても正にできないなら，なるべく絶対値を小さくする．
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

bool cmp(int a, int b) {
    return abs(a) < abs(b);
}

int main() {
    ios::sync_with_stdio(0);

    int N, K;
    cin >> N >> K;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end(), cmp);
    reverse(v.begin(), v.end());

    vector<int> ans;
    bool positive = true;
    int last_posi_pos = -1, last_neg_pos = -1;
    for(int i = 0; i < K; ++i) {
        ans.push_back(v[i]);
        if(v[i] < 0) {
            positive = !positive;
            last_neg_pos = i;
        }
        else {
            last_posi_pos = i;
        }
    }
    if(!positive) {
        double posi_pop_ratio = -INFINITY, neg_pop_ratio = -INFINITY;
        int posi_pos = -1, neg_pos = -1;
        for(int i = K; i < N; ++i) {
            if(last_posi_pos != -1 && posi_pos == -1 && v[i] < 0) {
                posi_pop_ratio = fabs((double)v[i]/ans[last_posi_pos]);
                neg_pos = i;
            }
            else if(neg_pos == -1 && v[i] >= 0) {
                neg_pop_ratio = fabs((double)v[i]/ans[last_neg_pos]);
                posi_pos = i;
            }
        }

        if(posi_pos == -1 && neg_pos == -1) {
            ans.clear();
            reverse(v.begin(), v.end());
            for(int i = 0; i < K; ++i) {
                ans.push_back(v[i]);
            }
        }
        else {
            if(posi_pop_ratio > neg_pop_ratio) {
                ans.erase(ans.begin()+last_posi_pos);
                ans.push_back(v[neg_pos]);
            }
            else {
                ans.erase(ans.begin()+last_neg_pos);
                ans.push_back(v[posi_pos]);
            }
        }
    }

    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    bool first = true;
    for(int i = 0; i < K; ++i) {
        if(!first) cout << ' ';
        cout << ans[i];
        first = false;
    }
    cout << endl;

    return 0;
}
