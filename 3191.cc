#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    set<long long> pos, neg;

    for(long long i = 0; i <= 0x1ffff; ++i) {
        long long d = 1;
        long long p = 0, n = 0;
        for(long long j = i; j; j >>= 1) {
            if(j & 1) {
                p += d;
                n += d<<1;
            }
            d <<= 2;
        }
        if(p < ((long long)abs(N))<<2) pos.insert(p);
        if(n < ((long long)abs(N))<<2) neg.insert(n);
    }
    pos.insert(0);
    neg.insert(0);

    long long pv = 0, nv = 0;
    if(N == 0) cout << 0;
    else if(N > 0) {
        for(set<long long>::iterator it = pos.begin(); it != pos.end(); ++it) {
            long long d = *it - N;
            if(neg.find(d) != neg.end()) {
                pv = *it;
                nv = d;
                break;
            }
        }
    }
    else {
        for(set<long long>::iterator it = neg.begin(); it != neg.end(); ++it) {
            long long d = *it + N;
            if(pos.find(d) != pos.end()) {
                nv = *it;
                pv = d;
                break;
            }
        }
    }

    bool head = true;
    for(int bit = 31; bit >= 0; --bit) {
        long long mask = (1<<bit);
        if(bit & 1) {
            if(nv & mask) {
                cout << 1;
                head = false;
            }
            else if(!head) cout << 0;
        }
        else {
            if(pv & mask) {
                cout << 1;
                head = false;
            }
            else if(!head) cout << 0;
        }
    }

    cout << endl;

    return 0;
}
