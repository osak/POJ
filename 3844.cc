//Name: Divisible Subsequences
//Level: 2
//Category: 累積和
//Note:

#include <cstdio>
#include <map>
#include <vector>

using namespace std;

int main() {
    int C;
    scanf("%d", &C);
    while(C--) {
        int D, N;
        scanf("%d %d", &D, &N);

        vector<int> m(D, 0);
        int sum = 0;
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            int n;
            scanf("%d", &n);
            sum += n;
            sum %= D;
            cnt += m[sum];
            if(sum == 0) ++cnt;
            m[sum]++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
