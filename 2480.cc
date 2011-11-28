#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> is_prime(1<<16, 1);
    is_prime[0] = is_prime[1] = 0;

    vector<int> primes;
    for(int i = 2; i < 1<<16; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i*i < 1<<16) {
                for(int j = i*i; j < 1<<16; j += i) is_prime[j] = 0;
            }
        }
    }

    int N;
    while(cin >> N) {
