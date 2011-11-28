#include <iostream>
#include <vector>
#include <complex>
#include <stack>

using namespace std;

vector<int> cars;

complex<int> dp[201][201];
complex<int> prev[201][201];

inline int abs(int n) {
    return (n<0) ? -n : n;
}

int main() {
    int flen;
    cin >> flen;
    flen *= 100;
    while(true) {
        int i;
        cin >> i;
        if(i == 0) break;
        cars.push_back(i);
    }

    for(int i = 0; i <= 200; ++i) {
        for(int j = 0; j <= 200; ++j) {
            dp[i][j] = complex<int>(flen+1, flen+1);
        }
    }

    dp[0][0] = complex<int>(0, 0);
    complex<int> best = complex<int>(0, 0);
    for(int i = 0; i <= cars.size(); ++i) {
        for(int j = 0; j <= cars.size(); ++j) {
            if(i == 0 && j == 0) continue;
            if(i+j > cars.size()) break;

            int diff = flen+1;
            if(i >= 1) {
                complex<int> l = dp[i-1][j] + complex<int>(cars[i+j-1], 0);
                if(l.real() <= flen) {
                    dp[i][j] = l;
                    prev[i][j] = complex<int>(i-1, j);
                    diff = abs(l.real() - l.imag());
                }
            }

            if(j >= 1) {
                complex<int> r = dp[i][j-1] + complex<int>(0, cars[i+j-1]);
                int diffr = abs(r.real() - r.imag());
                diffr = -1;
                if(r.imag() <= flen && diffr < diff) {
                    dp[i][j] = r;
                    prev[i][j] = complex<int>(i, j-1);
                }
            }
            if(dp[i][j].real() == flen+1 && dp[i][j].imag() == flen+1) {
    //            break;
            }
            else {
        //        cout << i << " " << j << " :" << dp[i][j] << endl;
            }
            if(dp[i][j].real() <= flen && dp[i][j].imag() <= flen) {
                int sum = best.real() + best.imag();
                if(i+j > sum) {
                    best = complex<int>(i, j);
                }
            }
        }
    }
endloop:
    cout << (best.real()+best.imag()) << endl;
    stack<bool> s;
    complex<int> curr = best;
    while(curr != complex<int>(0, 0)) {
        complex<int> p = prev[curr.real()][curr.imag()];
        if(p.real() != curr.real()) s.push(true);
        else s.push(false);
        curr = p;
    }
    while(!s.empty()) {
        bool b = s.top();
        s.pop();
        cout << (b ? "port" : "starboard") << endl;
    }
}
