//Name: Bin Packing
//Level: 2
//Category: 貪欲法,ダブルポインタ,Greedy
//Note:

/*
 * each bin contains at most 2 itemsの条件があるので、Itemをソートして先頭から、末尾からを順に対応させていけば良い。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, L;
    cin >> N >> L;
    vector<int> v(N);
    for(int i = 0; i < N; ++i) cin >> v[i];
    sort(v.begin(), v.end());

    int cnt = 0;
    int left = 0, right = N-1;
    while(left < right) {
        if(v[left]+v[right] <= L) {
            ++cnt; ++left; --right;
        }
        else {
            ++cnt; --right;
        }
    }
    if(left == right) ++cnt;
    cout << cnt << endl;
    return 0;
}
