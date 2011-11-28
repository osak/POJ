//Name: Scramble Sort
//Level: 2
//Category: ソート
//Note:

/*
 * カンマ区切りなので、文字列で1行読み込んでから自力でばらす。
 * 要素の種類の並び順を覚えておいて、別々にソートしてからまた戻す。
 */
#include <iostream>
#include <queue>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

bool word_greater(const string &s1, const string &s2) {
    char buf1[256], buf2[256];
    for(int i = 0; i < s1.length(); ++i) {
        buf1[i] = tolower(s1[i]);
    }
    for(int i = 0; i < s2.length(); ++i) {
        buf2[i] = tolower(s2[i]);
    }
    return strcmp(buf1, buf2) < 0;
}

int main() {
    while(true) {
        vector<string> words;
        vector<int> nums;
        queue<char> kind;

        string line;
        getline(cin, line);
        if(line[0] == '.') break;
        int prevpos = 0;
        int cnt = 0;
        while(prevpos < line.length()) {
            int comma = line.find_first_of(".,", prevpos);
            string sub = line.substr(prevpos, comma-prevpos);
            if(isalpha(sub[0])) {
                words.push_back(sub);
                kind.push('W');
            }
            else {
                nums.push_back(atoi(sub.c_str()));
                kind.push('N');
            }

            prevpos = comma+2;
            ++cnt;
        }

        sort(words.begin(), words.end(), &word_greater);
        sort(nums.begin(), nums.end());

        bool first = true;
        int wordpos = 0;
        int numpos = 0;
        while(!kind.empty()) {
            if(!first) cout << ", ";
            char c = kind.front();
            kind.pop();
            if(c == 'W') {
                cout << words[wordpos++];
            }
            else {
                cout << nums[numpos++];
            }
            first = false;
        }
        cout << "." << endl;
    }

    return 0;
}
