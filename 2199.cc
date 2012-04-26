//Name: Rate of Return
//Level: 1
//Category: 二分探索,やるだけ
//Note:

/*
 * 二分探索やるだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int CASE = 1; ; ++CASE) {
        int N;
        cin >> N;
        if(N == -1) break;

        vector<pair<int, double> > investments(N);
        for(int i = 0; i < N; ++i) {
            cin >> investments[i].first >> investments[i].second;
        }
        pair<int, double> last;
        cin >> last.first >> last.second;

        double left = 0, right = 1;
        for(int step = 0; step < 30; ++step) {
            double center = (left+right) / 2;
            double val = 0;
            for(int i = 0; i < N; ++i) {
                val += investments[i].second * pow(1+center, last.first - investments[i].first + 1);
            }
            if(val < last.second) {
                left = center;
            }
            else {
                right = center;
            }
        }

        cout.precision(5);
        cout.setf(ios::fixed);
        if(CASE > 1) cout << endl;
        cout << "Case " << CASE << ": " << (left+right)/2 << endl;
    }

    return 0;
}
