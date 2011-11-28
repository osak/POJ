#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool isprime[10000];

int main() {
    fill(&isprime[0], &isprime[9999], true);
    isprime[0] = isprime[1] = false;
    for(int i = 2; i < 10000; ++i) {
        if(!isprime[i]) continue;
        for(int j = i*i; j < 10000; j += i) {
            isprime[j] = false;
        }
    }

    int N;
    cin >> N;
    while(N--) {
        int a, b;
        cin >> a >> b;

        queue<pair<int, int> > q;
        vector<bool> used(10000, false);
        q.push(make_pair(0, a));
        while(!q.empty()) {
            int cnt = q.front().first;
            int num = q.front().second;
            q.pop();
            if(num == b) {
                cout << cnt << endl;
                break;
            }
            int n;
            for(int i = 0; i <= 9; ++i) {
                if(i != 0) {
                    n = i*1000 + num%1000;
                    if(!used[n] && isprime[n]) {
                        q.push(make_pair(cnt+1, n));
                        used[n] = true;
                    }
                }
                n = (num/1000)*1000 + i*100 + num%100;
                if(!used[n] && isprime[n]) {
                    q.push(make_pair(cnt+1, n));
                    used[n] = true;
                }
                n = (num/100)*100 + i*10 + num%10;
                if(!used[n] && isprime[n]) {
                    q.push(make_pair(cnt+1, n));
                    used[n] = true;
                }
                n = (num/10)*10 + i;
                if(!used[n] && isprime[n]) {
                    q.push(make_pair(cnt+1, n));
                    used[n] = true;
                }
            }
        }
    }
    return 0;
}
