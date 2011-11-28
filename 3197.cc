#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int numlen(ULL n) {
    int len = 1;
    while(n /= 10) ++len;
    return len;
}

string ull2str(ULL n) {
    string s;
    while(n) {
        s = string("") + (char)('0' + n%10) + s;
        n /= 10;
    }
    return s;
}

string rep(char c, int n) {
    string str;
    for(int i = 0; i < n; ++i) str += c;
    return str;
}

vector<string> gen(ULL n, vector<string> denom) {
    int dl = numlen(n);
    int denom_len = denom[0].size();
    vector<string> frac;
    frac.push_back(rep('.', dl+3+(denom_len-1)/2) + '1' + rep('.', denom_len/2));
    frac.push_back(ull2str(n) + ".+." + rep('-', denom_len));
    for(int i = 0; i < denom.size(); ++i) {
        frac.push_back(rep('.', dl+3) + denom[i]);
    }

    return frac;
}

int main() {
    for(int C = 1; ; ++C) {
        ULL p, q;
        cin >> p >> q;
        if(!p && !q) break;

        cout << "Case " << C << ":" << endl;
        cout << p << " / " << q << endl;
        vector<ULL> denoms;
        while(q != 0) {
            denoms.push_back(p / q);
            int mod = p % q;
            p = q;
            q = mod;
        }
        denoms[denoms.size()-1]--;

        vector<string> frac;
        frac.push_back("1");
        for(int i = denoms.size()-1; i >= 0; --i) {
            frac = gen(denoms[i], frac);
        }

        for(int i = 0; i < frac.size(); ++i) {
            cout << frac[i] << endl;
        }
    }
}
