//Name: Computer Transformation
//Level: 3
//Category: 多倍長,法則
//Note:

#include <iostream>
#include <vector>

using namespace std;

struct BigNum {
    vector<int> v;

    BigNum(int n) { v.push_back(n); }
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
        }

        return *this;
    }

    BigNum& operator +=(int n) {
        v[0] += n;
        int carry = 0;
        for(int i = 0; i < v.size(); ++i) {
            carry = v[i]/10;
            v[i] %= 10;
            if(carry == 0) break;
        }
        if(carry) {
            v.push_back(carry);
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

ostream& operator <<(ostream &os, const BigNum &bn) {
    for(int i = (int)bn.v.size()-1; i >= 0; --i) os << bn.v[i];
    return os;
}

int main() {
    vector<BigNum> v(1001);
    v[0] = 0;
    v[1] = 0;
    for(int i = 2; i <= 1000; ++i) {
        if(i % 2 == 0) v[i] = v[i-1]*2+1;
        else v[i] = v[i-1]*2+(-1);
    }

    int N;
    while(cin >> N) {
        cout << v[N] << endl;
    }
    return 0;
}
