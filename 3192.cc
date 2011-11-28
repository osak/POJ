#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<string> v(N);
    for(int i = 0; i < N; ++i)
        cin >> v[i];
    sort(v.begin(), v.end());

    int ans = 7*7*2;
    do {
        string str = v[0];
        for(int i = 1; i < N; ++i) {
            bool found = false;
            for(int pos = max(0, (int)str.size()-(int)v[i].size()); pos < str.size(); ++pos) {
                if(str[pos] != v[i][0]) continue;
                bool ok = true;
                for(int j = pos; j < str.size(); ++j) {
                    if(str[j] != v[i][j-pos]) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    str = str.substr(0, pos) + v[i];
                    found = true;
                    break;
                }
            }
            if(!found) str += v[i];
        }
        //cout << str << endl;
        ans = min(ans, (int)str.size());
    } while(next_permutation(v.begin(), v.end()));

    cout << ans << endl;
    return 0;
}

