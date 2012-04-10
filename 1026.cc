//Name: Cipher
//Level: 3
//Category: 行列,置換
//Note:

/*
 * 置換が列方向から見た状態で与えられているため，行方向に直してから累乗する．
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


vector<int> shuffle_pow(const vector<int> &tr, int n) {
    if(n == 1) return tr;

    const int N = tr.size();
    vector<int> half = shuffle_pow(tr, n/2);
    vector<int> res(tr.size());
    for(int i = 0; i < N; ++i) res[i] = half[half[i]];
    if(n % 2 == 1) {
        half.swap(res);
        for(int i = 0; i < N; ++i) res[i] = half[tr[i]];
    }

    return res;
}

int main() {
    ios::sync_with_stdio();

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> tr(N);
        for(int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            tr[a-1] = i;
        }

        while(true) {
            int K;
            string msg;
            cin >> K;
            if(!K) break;

            cin.ignore();
            getline(cin, msg);

            vector<int> tr_pow = shuffle_pow(tr, K);
            for(int i = 0; i < N; ++i) cout << (tr_pow[i]<msg.size() ? msg[tr_pow[i]] : ' ');
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
