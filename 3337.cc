//Name: Expression Evaluator
//Level: 2
//Category: 文字列,シミュレーション,やるだけ
//Note:

/*
 * 最初に空白をすべて取り除き、先頭からパースしていく。
 * 曖昧な入力はないので、+や-を読んだら++か--になっているかをチェックし、
 * 直前が変数だったかどうかで前置・後置が判断できる。
 */
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    int N;
    cin >> N;
    string s;
    getline(cin, s);
    while(N--) {
        string orgstr;
        getline(cin, orgstr);
        string str = "";
        for(int i = 0; i < orgstr.size(); ++i) if(!isspace(orgstr[i])) str += orgstr[i];
        vector<int> var(26);
        vector<bool> used(26, false);
        for(int i = 0; i < 26; ++i) var[i] = i+1;

        int val = 0;
        char prev = '+';
        for(int pos = 0; pos < str.size(); ++pos) {
            if(isspace(str[pos])) continue;
            if(str[pos] == '+') {
                if(str[pos+1] == '+') { //Increment
                    if(isalpha(prev)) {
                        var[prev-'a']++;
                    }
                    else {
                        char v = str[pos+2];
                        var[v-'a']++;
                    }
                    ++pos;
                }
                else {
                    prev = '+';
                }
            }
            else if(str[pos] == '-') {
                if(str[pos+1] == '-') { //Decrement
                    if(isalpha(prev)) {
                        var[prev-'a']--;
                    }
                    else {
                        char v = str[pos+2];
                        var[v-'a']--;
                    }
                    ++pos;
                }
                else {
                    prev = '-';
                }
            }
            else { //Variable
                char v = str[pos];
                if(prev == '+') val += var[v-'a'];
                else val -= var[v-'a'];
                prev = v;
                used[v-'a'] = true;
            }
        }

        cout << "Expression: " << orgstr << endl;
        cout << "value = " << val << endl;
        for(char c = 'a'; c <= 'z'; ++c) {
            if(used[c-'a']) cout << c << " = " << var[c-'a'] << endl;
        }
    }
    return 0;
}
