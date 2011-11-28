//Name: Prime Cuts
//Level: 2
//Category: 素数
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> primes;
    vector<int> is_prime(1001, 1);
    is_prime[0] = 0;
    primes.push_back(1);
    for(int i = 2; i < is_prime.size(); ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = i*i; j < is_prime.size(); j += i)
                is_prime[j] = 0;
        }
    }

    int N, C;
    while(cin >> N >> C) {
        int pos = 0;
        while(pos < primes.size() && primes[pos] <= N) ++pos;
        int center = pos / 2;
        cout << N << ' ' << C << ":";
        for(int i = max(0, center-C+pos%2); i < min(pos, center+C); ++i) {
            cout << ' ' << primes[i];
        }
        cout << endl;
        cout << endl;
    }
    return 0;
}
