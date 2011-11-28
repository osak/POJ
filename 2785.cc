//Name: 4 Values whose Sum is 0
//Level: 2
//Category: 二分探索,組み合わせ
//Note:

/*
 * A*B, C*Dの組に分けて考え、c∈C*Dに対してa∈A*Bかつa+c=0となるものがいくつあるか数える。
 * equal_rangeというSTL関数があるらしく、これを使うとlower_boundとupper_boundを両方求めてくれる。
 */
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int arr[4000*4000];
int main() {
    int N;
    scanf("%d", &N);
    vector<int> v[4];
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 4; ++j) {
            int n;
            scanf("%d", &n);
            v[j].push_back(n);
        }
    }

    for(int i = 0; i < 4; ++i) {
        sort(v[i].begin(), v[i].end());
    }

    int arrpos = 0;
    for(int i = 0; i < v[0].size(); ++i)
        for(int j = 0; j < v[1].size(); ++j)
            arr[arrpos++] = v[0][i]+v[1][j];
    sort(arr, &arr[arrpos]);

    int ans = 0;
    for(int i = 0; i < v[2].size(); ++i) {
        for(int j = 0; j < v[3].size(); ++j) {
            int n = -(v[2][i]+v[3][j]);
            pair<int*, int*> range = equal_range(arr, &arr[arrpos], n);
            ans += range.second-range.first;
        }
    }

    printf("%d\n", ans);
    return 0;
}
