//Name: Coding of Permutations
//Level: 2
//Category: 数論,Math,順列,Permutation
//Note:

/*
 * i番目にnをもってくるとき，それより若いパターンでi番目に1〜n-1(のうち上の桁で使われていないもの)がくるものが存在する．
 * このとき，i番目以降のパターンは(N-i-1)!通りある．
 */
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

struct BigNum {
    vector<int> v;

    explicit BigNum(int n) { v.push_back(n); }
    BigNum() { v.push_back(0); }

    BigNum& operator *=(int n) {
        int carry = 0;
        for(int i = 0; i < v.size(); ++i) {
            v[i] *= n;
            v[i] += carry;
            carry = v[i]/10;
            v[i] %= 10;
        }
        if(carry) {
            v.push_back(carry);
            for(int i = (int)v.size()-1; ; ++i) {
                if(v[i] < 10) break;
                carry = v[i] / 10;
                v[i] %= 10;
                v.push_back(carry);
            }
        }

        return *this;
    }

    BigNum& operator +=(int n) {
        int carry = n;
        for(int i = 0; i < v.size(); ++i) {
            v[i] += carry;
            carry = v[i]/10;
            v[i] %= 10;
            if(carry == 0) break;
        }
        if(carry) {
            v.push_back(carry);
        }
        return *this;
    }

    BigNum& operator +=(const BigNum &n) {
        int carry = 0;
        if(v.size() < n.v.size()) v.resize(n.v.size(), 0);
        int i;
        for(i = 0; i < n.v.size(); ++i) {
            v[i] += carry + n.v[i];
            carry = v[i] / 10;
            v[i] %= 10;
        }
        if(carry) {
            if(i == v.size()) v.push_back(carry);
            else {
                for(i; carry && i < v.size(); ++i) {
                    v[i] += carry;
                    carry = v[i]/10;
                    v[i] %= 10;
                }
                if(carry) v.push_back(carry);
            }
        }
        return *this;
    }
};

BigNum operator *(const BigNum &bn, int n) {
    BigNum b = bn;
    b *= n;
    return b;
}

BigNum operator +(const BigNum &bn, int n) {
    BigNum b = bn;
    b += n;
    return b;
}

BigNum operator +(const BigNum &b1, const BigNum &b2) {
    BigNum b = b1;
    return b += b2;
}

ostream& operator <<(ostream &os, const BigNum &bn) {
    for(int i = (int)bn.v.size()-1; i >= 0; --i) os << bn.v[i];
    return os;
}

BigNum fact(int n) {
    BigNum ans(1);
    for(int i = 1; i <= n; ++i) ans *= i;
    return ans;
}

int main() {
    vector<BigNum> v;
    while(true) {
        string str;
        cin >> str;
        if(str == "-1") break;

        for(int i = 0; i < str.size(); ++i) {
            if(!isdigit(str[i])) str[i] = ' ';
        }

        BigNum ans(0);
        istringstream is(str);
        int N;
        is >> N;
        vector<int> used(N+1, 0);
        used[0] = 1;
        for(int i = 0; i < N; ++i) {
            int num;
            is >> num;
            for(int j = 0; j < num; ++j) {
                if(!used[j]) ans += fact(N-i-1);
                //cout << i << ':' << j << ':' << ans << endl;
            }
            used[num] = 1;
        }
        ans += 1;
        v.push_back(ans);
    }

    for(int i = 0; i < v.size(); ++i) {
        if(i != 0) cout << ',';
        cout << v[i];
    }
    cout << endl;
    return 0;
}
