//Name: Pseudoprime numbers
//Level: 2
//Category: 素数,modpow
//Note:

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

int modpow(int a, int n, int m) {
    if(n == 0) return 1;
    if(n == 1) return a % m;
    int half = n / 2;
    int h = modpow(a, half, m);
    int h2 = (n&1) ? modpow(a, half+1, m) : h;

    return (int)((LL)h*h2 % m);
}

const int SIZE = 31630;
unsigned char is_prime[SIZE];
vector<int> primes;

int main() {
    int lim = sqrt(SIZE);
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    primes.push_back(2);
    for(int i = 4; i < lim; i += 2) is_prime[i] = 0;
    for(int i = 3; i < SIZE; i += 2) {
        if(is_prime[i]) {
            for(int j = i*i; j < SIZE; j += i) is_prime[j] = 0;
        }
        primes.push_back(i);
    }

    while(true) {
        int P, A;
        cin >> P >> A;
        if(!P && !A) break;

        bool ok = false;
        for(int i = 0; i < primes.size() && primes[i] < P; ++i) {
            if(P % primes[i] == 0) {
                ok = true;
                break;
            }
        }
        cout << (ok && modpow(A, P, P) == A ? "yes" : "no") << endl;
    }
    return 0;
}
