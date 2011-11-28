//Name: An Industrial Spy
//Level: 2
//Category: 素数,next_permutation
//Note:

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int lim = sqrt(10000000);
    vector<int> is_prime(10000000, 1);
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i < 10000000; ++i) {
        if(is_prime[i] && i <= lim) {
            for(int j = i*i; j < 10000000; j += i)
                is_prime[j] = 0;
        }
    }

    int N;
    cin >> N;
    while(N--) {
        string line;
        cin >> line;
        sort(line.begin(), line.end());
        set<int> used;
        int cnt = 0;
        do {
            int n = 0;
            for(int i = 0; i < line.size(); ++i) {
                n *= 10;
                n += line[i]-'0';
                if(used.count(n)==0 && is_prime[n]) {
                    ++cnt;
                    used.insert(n);
                }
            }
        } while(next_permutation(line.begin(), line.end()));

        cout << cnt << endl;
    }
    return 0;
}
