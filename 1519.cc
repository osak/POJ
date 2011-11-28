//Name: Digital Roots
//Level: 1
//Category: ひっかけ,やるだけ
//Note:

/*
 * たぶんものすごく長い入力がある．
 * （intで提出したらOLEしたため）
 */
#include <iostream>
#include <string>

using namespace std;

int d(int n) {
    int res = 0;
    while(n) {
        res += n%10;
        n /= 10;
    }
    if(res < 10) return res;
    return d(res);
}

int main() {
    while(true) {
        string str;
        cin >> str;
        if(str == "0") break;

        int n = 0;
        for(int i = 0; i < str.size(); ++i) n += str[i]-'0';
        cout << d(n) << endl;
    }
    return 0;
}
