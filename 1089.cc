//Name: Intervals
//Level: 2
//Category: 区間
//Note:

/*
 * 最初に全部読み込んでソートし，頭から見ていけばよい．
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int N;
    cin >> N;

    vector<pair<int, int> > v;
    while(N--) {
        int a, b;
        cin >> a >> b;
        v.push_back(make_pair(a, b));
    }
    sort(v.begin(), v.end());

    int start = v[0].first;
    int end = v[0].second;
    for(int i = 0; i < v.size(); ++i) {
        if(start <= v[i].first && v[i].first <= end) {
            end = max(end, v[i].second);
        }
        else {
            cout << start << ' ' << end << endl;
            start = v[i].first;
            end = v[i].second;
        }
    }
    cout << start << ' ' << end << endl;

    return 0;
}
