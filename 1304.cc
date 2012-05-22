//Name: World's Worst Bus Schedule
//Level: 2
//Category: 数学
//Note:

/*
 * 到着までにバスが何周していようと，最後の1巡だけを見ればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>
#include <numeric>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string cmd;
        cin >> cmd;
        if(cmd == "ENDOFINPUT") break;

        int N;
        cin >> N;
        cin.ignore(255, '\n');
        vector<vector<int> > vs(N);
        for(int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);
            istringstream is(line);
            int d;
            while(is >> d) {
                vs[i].push_back(d);
            }
        }

        int ans = INT_MAX;
        int arrival;
        cin >> arrival;
        cin >> cmd; // ignore "END"
        for(int i = 0; i < N; ++i) {
            const vector<int> &v = vs[i];
            int sum = accumulate(v.begin(), v.end(), 0);
            int rem = arrival % sum;
            if(rem == 0) {
                ans = min(ans, 0);
            }
            else {
                for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
                    rem -= *it;
                    if(rem <= 0) {
                        // *itが出てから帰ってくるまでに到着した．
                        ans = min(ans, -rem);
                        break;
                    }
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
