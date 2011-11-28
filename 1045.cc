//Name: Bode Plot
//Level: 1
//Category: 数学,やるだけ
//Note: インピーダンスの計算式知ってるのが前提？

/*
 * インピーダンスの公式に当てはめて終わり。
 * 問題文中の式から導出できるかは試していない。
 */
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    double V, R, C;
    int N;
    cin >> V >> R >> C >> N;
    while(N--) {
        double w;
        cin >> w;
        printf("%.3f\n", V*R/sqrt(R*R+1/(w*w)/(C*C)));
    }
    return 0;
}

