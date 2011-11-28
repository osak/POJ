//Name: MANAGER
//Level: 2
//Category: シミュレーション
//Note:

#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    bool first = true;
    while(true) {
        int N;
        if(!(cin >> N)) break;
        if(!first) cout << endl;
        first = false;

        int L;
        cin >> L;
        vector<int> v(L);
        for(int i = 0; i < L; ++i) cin >> v[i];
        sort(v.begin(), v.end());

        multiset<int> q;
        int policy = 1;
        int remove_cnt = 0;
        vector<int>::iterator it = v.begin();
        while(true) {
            string cmd;
            cin >> cmd;
            if(cmd == "a") {
                int n;
                cin >> n;
                q.insert(n);
            }
            else if(cmd == "r") {
                int removal = -1;
                if(q.size() > 0) {
                    if(policy == 1) {
                        removal = *q.begin();
                        q.erase(q.begin());
                    }
                    else {
                        removal = *q.rbegin();
                        q.erase(removal);
                    }
                }
                ++remove_cnt;
                if(it != v.end() && remove_cnt == *it) {
                    cout << removal << endl;
                    ++it;
                }
            }
            else if(cmd == "p") {
                cin >> policy;
            }
            else if(cmd == "e") {
                break;
            }
        }
    }

    return 0;
}
