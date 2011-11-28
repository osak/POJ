//Name: Haiku Review
//Level: 1
//Category: 文字列,やるだけ
//Note:

/*
 * 先頭から母音を数えていくだけ．
 * /がきたときは母音の連続判定がリセットされることに注意．
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
    while(true) {
        string s;
        getline(cin, s);
        if(s == "e/o/i") break;

        char ans = 'Y';
        int cnt = 0;
        int phase = 0;
        bool prev_is_syllable = false;
        for(int i = 0; i <= s.size(); ++i) {
            if(i == s.size() || s[i] == '/') {
                if(phase == 1) {
                    if(cnt != 7) {
                        ans = '2';
                        break;
                    }
                }
                else {
                    if(cnt != 5) {
                        ans = '0'+phase+1;
                        break;
                    }
                }
                ++phase;
                cnt = 0;
                prev_is_syllable = false;
                if(i == s.size()) break;
            }
            else {
                if(string("aeiouy").find(s[i]) != string::npos) {
                    if(!prev_is_syllable) ++cnt;
                    prev_is_syllable = true;
                }
                else {
                    prev_is_syllable = false;
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
