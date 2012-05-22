//Name: Blue Gene, Jr.
//Level: 1
//Category: シミュレーション,やるだけ
//Note: 問題文が読みにくい

/*
 * 問題文が読みにくいが，要するに先頭から順に読んで行って
 * ・数字ならその数だけ飛んだ場所を処理してからその数字を1減らす．0なら何もしない．
 * ・アルファベットなら次の文字を処理してから，ここより右で起きた変化回数%10に置換する
 * という操作をするように書いてある．
 * その通りに実装するだけ．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>

using namespace std;

int mutate(int pos, string &code) {
    if(pos >= code.size()) return 0;

    if(isalpha(code[pos])) {
        int cnt = mutate(pos+1, code);
        code[pos] = '0' + (cnt % 10);
        return cnt + 1;
    }
    else if(isdigit(code[pos])) {
        int val = code[pos] - '0';
        if(val == 0) return 0;
        int next = pos + val;
        int cnt = 0;
        if(next >= code.size()) {
            cnt = mutate(pos+1, code);
        }
        else {
            cnt = mutate(next, code);
        }
        --code[pos];
        return cnt + 1;
    }
    else {
        assert(0);
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        string cmd;
        cin >> cmd;
        if(cmd == "ENDOFINPUT") break;
        
        int N;
        cin >> N;
        string code;
        cin >> code;
        cin >> cmd; // ignore "END"

        mutate(0, code);
        cout << code << endl;
    }
    return 0;
}
