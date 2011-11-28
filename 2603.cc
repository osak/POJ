//Name: Brave balloonists
//Level: 1
//Category: 素数,素因数分解
//Note:

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    vector<int> is_prime(10000, 1);
    vector<int> primes;

    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i < is_prime.size(); ++i) {
        if(is_prime[i]) {
            for(int j = i*i; j < is_prime.size(); j += i) is_prime[j] = 0;
            primes.push_back(i);
        }
    }

    map<int,int> m;
    for(int i = 0; i < 10; ++i) {
        int N;
        cin >> N;
        for(int j = 0; j < primes.size() && primes[j] <= N; ++j) {
            int cnt = 0;
            while(N % primes[j] == 0) {
                ++cnt;
                N /= primes[j];
            }
            if(cnt) m[primes[j]] += cnt;
        }
        if(N > 1) m[N] += 1;
    }

    int ans = 1;
    for(map<int,int>::iterator it = m.begin(); it != m.end(); ++it) 
        ans *= it->second+1;

    cout << ans%10 << endl;
    return 0;
}
