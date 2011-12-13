//Name: Binary Search
//Level: 2
//Category: 二分探索,Binary Search
//Note:

/*
 * [0, N-1]からL回の二分探索でちょうどIに到達するようなNを求める．
 * N<=10000, L<=14と小さいため，全てのNで実際に二分探索すればよい．
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int I, L;
    cin >> I >> L;

    vector<int> possibles;
    for(int n = 1; n <= 10000; ++n) {
        int left = 0, right = n-1;
        int l = 0;
        while(left <= right) {
            int center = (left+right)/2;
            ++l;
            if(center == I) break;
            if(I < center) right = center-1;
            else left = center+1;
        }
        if((left+right)/2 == I && l == L) possibles.push_back(n);
    }

    if(possibles.size() == 0) cout << 0 << endl;
    else {
        vector<pair<int,int> > v;
        int start = possibles[0];
        for(int i = 1; i < possibles.size(); ++i) {
            if(possibles[i] == possibles[i-1]+1) continue;
            else {
                v.push_back(make_pair(start, possibles[i-1]));
                start = possibles[i];
            }
        }
        v.push_back(make_pair(start, possibles.back()));

        cout << v.size() << endl;
        for(int i = 0; i < v.size(); ++i) cout << v[i].first << ' ' << v[i].second << endl;
    }
    return 0;
}
