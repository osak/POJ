//Name: Mileage Bank
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    int sum = 0;
    while(true) {
        string a, b;
        int m;
        char c;

        cin >> a;
        if(a == "0") {
            cout << sum << endl;
            sum = 0;
            continue;
        }
        if(a == "#") break;

        cin >> b >> m >> c;
        if(c == 'F') sum += m * 2;
        else if(c == 'B') sum += ceil(m * 1.5);
        else if(c == 'Y') {
            if(m < 500) sum += 500;
            else sum += m;
        }
    }
    return 0;
}
