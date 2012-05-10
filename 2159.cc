//Name: Ancient Cipher
//Level: 1
//Category: 文字列
//Note:

/*
 * それぞれの文字列で，「n回現れる文字の個数」を一覧にする．
 * これが一致すればYES．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> countfreq(const string &str) {
    vector<int> freq(26, 0);
    for(string::const_iterator it = str.begin(); it != str.end(); ++it) {
        freq[*it-'A']++;
    }

    vector<int> res(101, 0);
    for(vector<int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        res[*it]++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string str1, str2;
    cin >> str1 >> str2;

    if(countfreq(str1) == countfreq(str2)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
