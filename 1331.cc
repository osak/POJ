//Name: Multiply
//Level: 1
//Category: 数学,やるだけ
//Note:

/*
 * 進数変換するだけ．
 * p,q,rの範囲上，long longでないとオーバーフローのおそれがあることに注意．
 */
#include <iostream>
#include <algorithm>

using namespace std;

int max_digit(int n) {
    int ans = 0;
    while(n) {
        ans = max(ans, n%10);
        n /= 10;
    }
    return ans;
}

long long convert(int n, int base) {
    long long res = 0;
    long long b = 1;
    while(n) {
        res += (n%10) * b;
        n /= 10;
        b *= base;
    }
    return res;
}

int main() {
    int T;
    cin >> T;

    while(T--) {
        int p,q,r;
        cin >> p >> q >> r;
        int ans = 0;
        for(int b = max(max_digit(p), max(max_digit(q), max_digit(r)))+1; b <= 16; ++b) {
            if(convert(p, b) * convert(q, b) == convert(r, b)) {
                ans = b;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
