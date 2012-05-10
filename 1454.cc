//Name: Factorial Frequencies
//Level: 2
//Category: 多倍長,BigNum
//Note:

/*
 * 多倍長でN!を求めて数字を数えるだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        BigNum n(1);
        for(int i = 2; i <= N; ++i) {
            n *= i;
        }

        vector<int> freq(10, 0);
        for(vector<int>::iterator it = n.v.begin(); it != n.v.end(); ++it) {
            freq[*it]++;
        }

        cout << N << "! --" << endl;
        for(int i = 0; i < 5; ++i) {
            if(i != 0) cout << ' ';
            cout << "   (" << i << ")";
            cout.width(5);
            cout << freq[i];
            cout.width(0);
        }
        cout << endl;
        for(int i = 5; i <= 9; ++i) {
            if(i != 5) cout << ' ';
            cout << "   (" << i << ")";
            cout.width(5);
            cout << freq[i];
            cout.width(0);
        }
        cout << endl;
    }
    
    return 0;
}
