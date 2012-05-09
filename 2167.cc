//Name: Irrelevant Elements
//Level: 3
//Category: 素数,素因数分解
//Note:

/*
 * i番目の要素(0-origin)は最終的にcomb(N-1, i)の係数がかかる．
 * この係数がMで割り切れるとき，i番目の要素は無関係になる．
 * combinationとMを両方とも素因数分解して持っておけばよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_PRIME = 33000;
bool is_prime[MAX_PRIME];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<int> primes;
    for(int i = 0; i < MAX_PRIME; ++i) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < MAX_PRIME; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = i*i; j < MAX_PRIME; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int N, M;
    cin >> N >> M;
    vector<int> ans;
    map<int, int> m_factors;
    int tmp = M;
    for(vector<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
        if(tmp < *it) break;
        while(tmp % *it == 0) {
            m_factors[*it]++;
            tmp /= *it;
        }
    }
    if(tmp > 1) m_factors[tmp]++;

    vector<pair<int,int> > v;
    for(map<int,int>::iterator it = m_factors.begin(); it != m_factors.end(); ++it) {
        v.push_back(*it);
    }

    vector<int> fact_cnt(v.size(), 0);
    for(int i = 2; i <= N; ++i) {
        int num = N-(i-1);
        int den = i-1;
        bool irr = true;
        for(int j = 0; j < (int)v.size(); ++j) {
            const pair<int,int> mf = v[j];
            while(num % mf.first == 0) {
                fact_cnt[j]++;
                num /= mf.first;
            }
            while(den % mf.first == 0) {
                fact_cnt[j]--;
                den /= mf.first;
            }
            if(fact_cnt[j] < mf.second) {
                irr = false;
            }
        }
        if(irr) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        if(i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << endl;

    return 0;
}
