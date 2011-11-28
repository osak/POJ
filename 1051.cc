//Name: P,MTHBGWB
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

/*
 * やるだけ。
 * モールス符号→文字と文字→モールス符号の変換テーブルを両方用意しておき、
 * 問題文の通りに変換するだけ。
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string table[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
};

int main() {
    map<string, char> m;
    map<char, string> rev;
    for(int i = 0; i < 26; ++i) {
        m[table[i]] = 'A'+i;
    }
    m["..--"] = '_';
    m["---."] = '.';
    m[".-.-"] = ',';
    m["----"] = '?';

    for(map<string, char>::iterator it = m.begin(); it != m.end(); ++it) rev[it->second] = it->first;

    int N;
    cin >> N;
    for(int C = 1; C <= N; ++C) {
        string str;
        cin >> str;

        vector<int> len;
        string morse;
        for(int i = 0; i < str.size(); ++i) {
            const string &code = rev[str[i]];
            morse += code;
            len.push_back(code.size());
        }
        int pos = 0;
        cout << C << ": ";
        for(int i = 0; i < len.size(); ++i) {
            cout << m[morse.substr(pos, len[len.size()-i-1])];
            pos += len[len.size()-i-1];
        }
        cout << endl;
    }
    return 0;
}

