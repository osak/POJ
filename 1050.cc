//Name: To the Max
//Level: 2
//Category: 動的計画法,全探索,DP
//Note: 

/*
 * 最初の行列を変形し、「(0,0)要素が左上のとき、この要素が右下になる矩形で合計はいくらになるか」
 * を保持しておく。
 * あとは左上座標と右下座標を決めると、その矩形内の合計が算出できる。
 * O(N^4)。頑張るとO(N^3)に出来る。
 */
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int> > v(N+1, vector<int>(N+1, 0));
    for(int i = 1; i < N+1; ++i) 
        for(int j = 1; j < N+1; ++j)
            cin >> v[i][j];

    for(int i = 1; i < N+1; ++i)
        for(int j = 1; j < N+1; ++j)
            v[i][j] += v[i-1][j] + v[i][j-1] - v[i-1][j-1];

    int ans = INT_MIN;
    for(int i = 0; i < N+1; ++i) 
        for(int j = 0; j < N+1; ++j) 
            for(int k = 0; k < i; ++k) 
                for(int l = 0; l < j; ++l) 
                    ans = max(ans, v[i][j]-v[i][l]-v[k][j]+v[k][l]);

    cout << ans << endl;
    return 0;
}
