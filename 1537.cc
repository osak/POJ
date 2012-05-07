//Name: Identifying Legal Pascal Real Constants
//Level: 2
//Category: 構文解析
//Note:

/*
 * 問題文の通りに構文解析するだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

typedef string::iterator Iterator;

void trim(string &str) {
    Iterator it = str.begin();
    while(it != str.end() && *it == ' ') ++it;
    str.erase(str.begin(), it);
    if(str.size() > 0) {
        Iterator it = str.end()-1;
        while(it != str.begin() && *it == ' ') --it;
        if(*it != ' ') ++it;
        str.erase(it, str.end());
    }
}

void skip(Iterator &it, char c, const Iterator &end) {
    if(it == end || tolower(*it) != c) {
        throw "Unexpected char";
    }
    ++it;
}

void integer(Iterator &it, const Iterator &end) {
    if(it == end) throw "End of line";
    if(*it == '-' || *it == '+') skip(it, *it, end);
    if(it == end || !isdigit(*it)) throw "Not an integer";
    while(it != end && isdigit(*it)) ++it;
}

bool valid(Iterator &it, const Iterator &end) {
    integer(it, end);
    if(it == end || *it == '.') {
        skip(it, '.', end);
        integer(it, end);
    }
    if(it != end) {
        skip(it, 'e', end);
        integer(it, end);
    }
    return it == end;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string line;
        getline(cin, line);
        if(line == "*") break;

        trim(line);
        Iterator it = line.begin();
        bool res = true;
        try {
            res = valid(it, line.end());
        } catch(const char *str) {
            res = false;
        }
        cout << line << " is " << (res ? "" : "il") << "legal." << endl;
    }

    return 0;
}
