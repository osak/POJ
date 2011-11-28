#include <iostream>
#include <string>
#include <climits>

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    if(s1.length() < s2.length()) {
        string tmp = s1;
        s1 = s2;
        s2 = tmp;
    }
    int bestlen = s1.length()+s2.length();
    for(int i = -1*(int)s2.length(); i < (int)s1.length(); ++i) {
        bool ok = true;
        for(int j = 0; j < s2.length(); ++j) {
            if(i+j < 0) continue;
            if(i+j >= s1.length()) continue;
            if(s2[j]=='2' && s1[i+j]=='2') {
                ok = false;
                break;
            }
        }
        if(ok) {
            int len;
            if(i < 0) len = -i+s1.length();
            else if(i > s1.length()-s2.length()) len = s1.length()+(i+s2.length()-s1.length());
            else len = s1.length();
            if(len < bestlen) {
                bestlen = len;
            }
        }
    }

    cout << bestlen << endl;

    return 0;
}
