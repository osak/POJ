#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == -1) break;

        vector<int> w(N), h(N);
        for(int i = 0; i < N; ++i) {
            cin >> w[i] >> h[i];
            if(i > 0) w[i] += w[i-1];
        }

        
