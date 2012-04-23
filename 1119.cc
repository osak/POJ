//Name: Start Up the Startup
//Level: 2
//Category: 実装
//Note:

/*
 * 問題文の通りに実装するだけ．
 * ・一つのdocumentは複数行で構成される（search stringも例外ではない）
 * ・記号は空白にするのではなく削除する
 * という点に注意する．
 */
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <cmath>

using namespace std;

void normalize(string &str) {
    string::iterator it = str.begin();
    while(it != str.end()) {
        if(!isspace(*it) && !isalnum(*it)) {
            it = str.erase(it);
            continue;
        }
        else if(isupper(*it)) {
            *it = tolower(*it);
        }
        ++it;
    }
}

string& readdoc(string &str) {
    while(true) {
        string line;
        getline(cin, line);
        if(line == "----------") break;
        normalize(line);
        str += " ";
        str += line;
    }
    return str;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    map<string,int> dict;
    {
        string doc;
        readdoc(doc);

        istringstream is(doc);
        string token;
        while(is >> token) {
            dict[token]++;
        }
    }

    while(!cin.eof()) {
        map<string,int> cnt;
        string doc;
        readdoc(doc);
        if(doc == "") break;
        istringstream is(doc);
        string token;
        while(is >> token) {
            cnt[token]++;
        }

        double score = 0;
        for(map<string,int>::iterator it = dict.begin(); it != dict.end(); ++it) {
            score += sqrt(it->second*cnt[it->first]);
        }
        cout.precision(2);
        cout.setf(ios::fixed);
        cout << score << endl;
    }

    return 0;
}
