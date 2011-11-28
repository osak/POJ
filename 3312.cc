#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

bool cmp(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

int main() {
    for(int C = 1; ; ++C) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;

        vector<int> v;
        for(int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            v.push_back(s.size());
        }

        sort(v.begin(), v.end());

        bool ok = true;
        for(int i = 0; i < N; i += K) {
            int sum = 0;
            for(int j = 0; j < K; ++j) sum += v[i+j];
            double avg = (double)sum / K;

            for(int j = 0; j < K; ++j) {
                if(abs(avg-v[i+j]) > 2) {
                    ok = false;
                    break;
                }
            }
            if(!ok) {
                break;
            }
        }

        cout << "Case " << C << ": " << (ok?"yes":"no") << endl;
        cout << endl;
    }
    return 0;
}

