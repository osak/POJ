//Name: u Calculate e
//Level: 2
//Category: 数学,数値計算
//Note:

/*
 * 式をそのまま計算すると有効桁数が足りないので通分してから足す．
 */
#include <cstdio>

using namespace std;

int main() {
    puts("n e");
    puts("- -----------");
    for(int n = 0; n <= 9; ++n) {
        int fact = 1;
        for(int i = 1; i <= n; ++i) fact *= i;
        int sum = 0;
        int sub = fact;
        for(int i = 0; i <= n; ++i) {
            if(i > 0) sub /= i;
            sum += sub;
        }
        double e = (double)sum / fact;
        printf("%d %.9f\n", n, e);
    }
    return 0;
}
