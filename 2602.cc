//Name: Superlong sums
//Level: 1
//Category: 筆算,やるだけ
//Note:

#include <cstdio>
#include <cstring>

char n1[1000002], n2[1000002];

int main() {
    int N;
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        scanf("%d %d", n1+i, n2+i);
    }
    int carry = 0;
    for(int i = 0; i < N; ++i) {
        int idx = N-i;
        int tmp = n1[idx]+n2[idx]+carry;
        n1[idx] = tmp % 10 + '0';
        carry = (tmp >= 10);
    }
    if(carry) {
        n1[0] = '1';
        puts(n1);
    }
    else {
        puts(n1+1);
    }
    return 0;
}
