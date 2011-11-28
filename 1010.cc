#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    while(!cin.eof()) {
        vector<int> stamps;
        while(true) {
            int s;
            cin >> s;
            if(s == 0) break;
            stamps.push_back(s);
        }
        sort(stamps.begin(), stamps.end());

        //[nums][kinds]
        vector<int> dp[25];


        for(int i = 0; i < stamps.size(); ++i) {
        }

        while(true) {
            int q;
            cin >> q;
            if(q == 0) break;
        }
    }
}
