//Name: Ball Toss
//Level: 2
//Category: シミュレーション
//Note: 英語読解ゲー

/*
 * 基本的にはシミュレーションやるだけ……なのだが英語がクソ．
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int K;
        cin >> K;
        K--;
        vector<char> v(N);
        for(int i = 0; i < N; ++i) cin >> v[i];

        vector<int> used(N, 0);
        int cur = K, prev = 0;
        int cnt = 0;
        int last;
        int turn;
        for(turn = 1; cnt < N; ++turn) {
            //if(turn < 10) cout << cur << endl;
            if(!used[cur]) {
                used[cur] = 1;
                ++cnt;
                last = cur;
            }
            int next;
            if(v[cur] == 'L') {
                next = (prev+N-1) % N;
                if(prev == (cur+1)%N) next = (cur+N-1) % N;
                v[cur] = 'R';
            }
            else {
                next = (prev+1) % N;
                if(prev == (cur+N-1)%N) next = (cur+1) % N;
                v[cur] = 'L';
            }
            prev = cur;
            cur = next;
        }
        cout << "Classmate " << last+1 << " got the ball last after " << turn-1 << " tosses." << endl;
    }

    return 0;
}
