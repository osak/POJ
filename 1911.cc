//Name: A Well-Formed Problem
//Level: 2
//Category: 構文解析,やるだけ,強実装
//Note:

/*
 * やるだけ．文字列はすべてすっ飛ばして，タグだけ見ていけばよい．
 *
 * 問題文中のwell-formed条件はサンプルがだいたい網羅している．
 * サンプルにない注意点としては，
 * ・空タグ(<hoge />)
 * ・ルートに空タグ複数出てくる
 * ・値のないattribute
 * など．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

typedef string::iterator Iterator;

enum Type { TAG_OPEN, TAG_CLOSE, TAG_ALONE };

void debug_print(Iterator it, const Iterator &end) {
    while(it != end) cout << *it++;
    cout << endl;
}

bool check(Iterator &it, const Iterator &end, char c) {
    return (it != end && *it == c);
}

void skip_until(Iterator &it, const Iterator &end, char c, bool end_is_error) {
    while(it != end && *it != c) ++it;
    if(it == end && end_is_error) throw "Unexpected end";
}

void skip_white(Iterator &it, const Iterator &end) {
    while(it != end && isspace(*it)) ++it;
}

void skip(Iterator &it, const Iterator &end, char c) {
    if(it == end) throw "Unexpected end";
    if(*it != c) throw "Unexpected character";
    ++it;
    skip_white(it, end);
}

string name(Iterator &it, const Iterator &end) {
    string str = "";

    skip_white(it, end);
    while(it != end && (isalnum(*it) || *it == '-')) str += *it++;
    skip_white(it, end);

    return str;
}

pair<string,Type> tag(Iterator &it, const Iterator &end) {
    Type type = TAG_OPEN;

    skip(it, end, '<');
    if(check(it, end, '/')) { // 閉じタグの判別
        skip(it, end, '/');
        type = TAG_CLOSE;
    }

    string tagname = name(it, end);
    if(type == TAG_OPEN) {
        set<string> attrs;
        while(!check(it, end, '/') && !check(it, end, '>')) {
            string attrname = name(it, end);

            // 4. attributeはダブらない
            if(attrs.count(attrname)) throw "Duplicated attribute";

            // 6. attributeは値を持つ
            skip(it, end, '=');
            skip(it, end, '"');
            skip_until(it, end, '"', true);
            skip(it, end, '"');
            attrs.insert(attrname);
        }

        if(check(it, end, '/')) {
            skip(it, end, '/');
            type = TAG_ALONE;
        }
    }

    skip(it, end, '>');
    return make_pair(tagname, type);
}

void parse(Iterator &it, const Iterator &end) {
    vector<string> stk;
    bool first = true;

    skip_white(it, end);
    while(check(it, end, '<')) {
        pair<string,Type> t = tag(it, end);
        //cout << t.first << endl;

        if(stk.size() == 0 && !first) {
            // 1. ルート要素は1つでなければならない
            throw "Too many roots";
        }
        if(t.second != TAG_CLOSE && find(stk.begin(), stk.end(), t.first) != stk.end()) {
            // 5. 同名タグは入れ子にならない
            throw "Recursive reference";
        }

        if(t.second == TAG_OPEN) {
            stk.push_back(t.first);
            first = false;
        }
        else if(t.second == TAG_CLOSE) {
            if(stk.size() == 0 || stk.back() != t.first) {
                // 2,3. タグは正常にネストしないといけない
                throw "Unmatched tag";
            }
            stk.pop_back();
        }
        skip_until(it, end, '<', false);
    }

    // 2. タグは必ず閉じなければならない
    if(stk.size() > 0) throw "Unclosed tag";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    {
        // Skip first header
        string line;
        getline(cin, line);
    }

    bool end = false;
    while(!end) {
        string txt;
        while(true) {
            string line;
            getline(cin, line);
            if(line == "<?end?>") {
                end = true;
                break;
            }
            if(line == "<?xml version=\"1.0\"?>") break;
            txt += " ";
            txt += line;
        }

        bool well_formed = true;
        try {
            Iterator it = txt.begin();
            parse(it, txt.end());
        } catch(const char *str) {
            //cout << str << endl;
            well_formed = false;
        }

        cout << (well_formed?"" : "non ") << "well-formed" << endl;
    }

    return 0;
}
