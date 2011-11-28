//Name: Barbara Bennett's Wild Numbers
//Level: 2
//Category: 文字列、数論、深さ優先探索
//Note:

/*
 * WとXは同じ長さと仮定する。
 * WとXの同じ位置にある数字を比べたとき、
 * ・Wの方が小さい・・・それ以降は?が何になっても0通り
 * ・Wの方が大きい・・・それ以降の?は何になっても通る
 * ・同じ・・・次の数字によって決まる
 * ・Wが?・・・Xの数字より大きくとれば「Wの方が大きい」のパターン。
 * 　　　　　　Xの数字と同じにすると、「同じ」のパターン
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<int> wildcnt(11, 0);
string X;

long long dfs(const string w, int pos) {
    if(pos >= w.size()) return 0;
    if(w[pos] == '?') {
        long long sum = pow(10, wildcnt[pos+1]) * ('9'-X[pos]);
        return sum + dfs(w, pos+1);
    }
    if(w[pos] < X[pos]) return 0;
    if(w[pos] > X[pos]) return pow(10, wildcnt[pos+1]);
    return dfs(w, pos+1);
}

int main() {
    while(true) {
        string w, x;
        cin >> w;
        if(w == "#") break;
        cin >> X;

        if(X.size() > w.size()) cout << 0 << endl;
        while(X.size() < w.size()) X = '0' + X;
        fill(wildcnt.begin(), wildcnt.end(), 0);
        for(int i = w.size()-1; i >= 0; --i) {
            wildcnt[i] = wildcnt[i+1] + (w[i]=='?' ? 1 : 0);
        }
        cout << dfs(w, 0) << endl;
    }
    return 0;
}
