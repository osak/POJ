#include <iostream>

using namespace std;

int price[5000];
int maxbuy[5000];
int maxlen;

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> price[i];
        maxbuy[i] = 1;
        vector<int> v;
        v.push_back(price[i]);
        sequence[i].push_back(v);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(price[i] < price[j]) {
                if(maxbuy[j]+1 > maxbuy[i]) {
                    maxbuy[i] = maxbuy[j]+1;
                    if(maxbuy[i] > maxlen) maxlen = maxbuy[i];
                }
            }
        }
        for(int j = 0; j < i; ++j) {
            if(maxbuy[j] == maxbuy[i]-1) {
                for(int k = 0; k < sequence[j].size(); ++k) {
                    vector<int> v = sequence[j][k];
                    v.push_back(price[i]);
                    sequence[i].push_back(v);
                    ++pattern[i];
                }
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(maxbuy[i] == maxlen) cnt += pattern[i];
        //cout << price[i] << " " << maxbuy[i] << endl;
    }

    cout << maxlen << " " << cnt << endl;
    return 0;
}
