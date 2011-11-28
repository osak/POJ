#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    while(N--) {
        string s1, s2;
        cin >> s1 >> s2;

        bool yes = false;
        for(int C = 0; C <= 1; ++C) {
            int p2 = 0;
            for(int i = 0; i < s1.size(); ++i) {
                if(s1[i] == s2[p2]) {
                    ++p2;
                    if(p2 == s2.size()) {
                        yes = true;
                        goto end;
                    }
                }
            }
            reverse(s2.begin(), s2.end());
        }
end:
        cout << (yes?"YES":"NO") << endl;
    }
    return 0;
}
