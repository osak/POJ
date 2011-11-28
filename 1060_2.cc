//Name: Modular multiplication of polynomials
//Level: 2
//Category: シミュレーション
//Note:

/*
 * 係数がmod 2なので、XORを使ってパタパタとひっくり返していけば良い。
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    while(N--) {
        vector<int> f,g,h;
        int fd, gd, hd;
        cin >> fd;
        f.resize(fd+1000);
        for(int i = 0; i < fd; ++i) cin >> f[fd-i-1];
        cin >> gd;
        g.resize(gd+1000);
        for(int i = 0; i < gd; ++i) cin >> g[gd-i-1];
        cin >> hd;
        h.resize(hd+1000);
        for(int i = 0; i < hd; ++i) cin >> h[hd-i-1];

        vector<int> coef(fd+gd, 0);
        for(int i = 0; i < fd; ++i)
            for(int j = 0; j < gd; ++j) 
                coef[i+j] ^= f[i]&g[j];

        for(int i = (int)fd+gd-1; i >= hd-1; --i) 
            if(coef[i]) 
                for(int j = 0; j < hd; ++j) coef[i-j] ^= h[hd-j-1];

        int k = hd;
        while(!coef[k]) --k;
        cout << k+1;
        while(k>=0) cout << " " << coef[k--];
        cout << endl;
    }
    return 0;
}
