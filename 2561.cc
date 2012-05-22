//Name: Language Cardinality
//Level: 2
//Category: 文字列,探索
//Note:

/*
 * multimapで変換辞書を作って，既出の文字列をキャッシュしながらナイーブに探索する．
 * 1000を超えたら打ち切ってよいので，なるべく無駄な探索をしない(新しい文字列を生成しやすくする)ために，BFSではなくDFSをしている．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

string& unquote(string &str) {
    string::iterator it = str.begin();
    while(it != str.end()) {
        if(*it == '"') it = str.erase(it);
        else ++it;
    }
    return str;
}

set<string> dict;
multimap<string,string> rules;
void dfs(const string &str) {
    for(multimap<string,string>::iterator it = rules.begin(); it != rules.end(); ++it) {
        size_t pos = 0;
        while((pos = str.find(it->first, pos)) != string::npos) {
            string next = str;
            next.replace(pos, it->first.size(), it->second);
            if(dict.count(next) == 0) {
                dict.insert(next);
                if(dict.size() > 1000) throw "Too many.";
                dfs(next);
            }
            pos += it->first.size();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string init;
    cin >> init;
    unquote(init);

    string line;
    while(cin >> line) {
        size_t hyphen = line.find('-');
        string lhs = line.substr(0, hyphen);
        string rhs = line.substr(hyphen+2);
        rules.insert(make_pair(unquote(lhs), unquote(rhs)));
    }

    dict.insert(init);
    try {
        dfs(init);
    } catch (const char *str) {
    }

    if(dict.size() > 1000) cout << "Too many." << endl;
    else cout << dict.size() << endl;

    return 0;
}
