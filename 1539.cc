//Name: Evaluating Simple C Expressions
//Level: 2
//Category: 文字列,構文解析
//Note:

/*
 * 曖昧な演算がないので，前か後ろに変数のある++は必ずインクリメント演算子になる．
 * これらを見つけ次第記録して消去していくと，最終的には2項演算のみが残るので簡単に計算できる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string str;
        getline(cin, str);
        if(str == "") break;

        vector<int> used(26, 0), pre(26, 0), post(26, 0);
        string org = str;

        size_t pos;
        while((pos = str.find("++")) != string::npos) {
            int cur = pos-1;
            while(cur >= 0 && str[cur] == ' ') --cur;
            if(cur >= 0 && isalpha(str[cur])) {
                post[str[cur]-'a']++;
                str.erase(pos, 2);
                continue;
            }

            cur = pos+2;
            while(cur < str.size() && str[cur] == ' ') ++cur;
            if(cur < str.size() && isalpha(str[cur])) {
                pre[str[cur]-'a']++;
                str.erase(pos, 2);
            }
        }
        while((pos = str.find("--")) != string::npos) {
            int cur = pos-1;
            while(cur >= 0 && str[cur] == ' ') --cur;
            if(cur >= 0 && isalpha(str[cur])) {
                post[str[cur]-'a']--;
                str.erase(pos, 2);
                continue;
            }

            cur = pos+2;
            while(cur < str.size() && str[cur] == ' ') ++cur;
            if(cur < str.size() && isalpha(str[cur])) {
                pre[str[cur]-'a']--;
                str.erase(pos, 2);
            }
        }

        int acc = 0;
        char op = '+';
        for(int i = 0; i < (int)str.size(); ++i) {
            if(str[i] == ' ') continue;
            if(isalpha(str[i])) {
                int idx = str[i] - 'a';
                int val = idx+1 + pre[idx];
                used[idx] = true;
                if(op == '+') acc += val;
                else if(op == '-') acc -= val;
            }
            else {
                op = str[i];
            }
        }
        cout << "Expression: " << org << endl;
        cout << "    value = " << acc << endl;
        for(int i = 0; i < 26; ++i) {
            if(used[i]) {
                cout << "    " << char(i+'a') << " = " << (i+1+pre[i]+post[i]) << endl;
            }
        }
    }

    return 0;
}
