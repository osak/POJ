#include <iostream>
#include <cstring>

using namespace std;

int a,b,c,d,e,f,g,h;

int abs(int n) {
    return (n<0) ? -n : n;
}

int mod(int n, int m) {
    if(n < 0) n += m * (1 + abs(n)/m);
    return n % m;
}

int cache[1001];

int func(int i) {
    if(i == 0) return a;
    if(i == 1) return b;
    if(i == 2) return c;

    if(cache[i] == -1) {
        if(i%2) cache[i] =  mod(d*func(i-1) + e*func(i-2) - f*func(i-3), g);
        else cache[i] =  mod(f*func(i-1) - d*func(i-2) + e*func(i-3), h);
    }
    return cache[i];
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        int i;
        cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
        for(int k = 0; k <= 1000; ++k) cache[k] = -1;
        cout << func(i) << endl;
    }

    return 0;
}
