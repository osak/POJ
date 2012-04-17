//Name: The Counting Problem
//Level: 3
//Category: 数値，探索
//Note:

/*
 * たとえば54321のような数を考えると，0から54321までの数字の合計は
 * ・0****の数字の合計（ただし，leading zeroを数えないことに注意）
 * ・2****の数字の合計
 * ・3****の数字の合計
 * ・4****の数字の合計
 * ・50000から54321の数字の合計
 * と表せる．つまり先頭1桁を固定すると，それより下の桁の個数を再帰的に求めて足すことで分割統治ができる．
 * あとはメモ化すればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

struct Tag {
    int n, ord;
    bool top;
    Tag() {}
    Tag(int n, int o, bool t) : n(n), ord(o), top(t) {}

    bool operator <(const Tag &other) const {
        if(n != other.n) return n < other.n;
        else if(ord != other.ord) return ord < other.ord;
        return top < other.top;
    }

    bool operator ==(const Tag &other) const {
        return n == other.n && ord == other.ord && top == other.top;
    }
};

ostream& operator <<(ostream &o, const vector<int> &v) {
    for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        o << *it << ' ';
    }

    return o;
}

map<Tag,vector<int> > memo;
vector<int> rec(int n, int ord, bool top) {
    vector<int> res(10, 0);
    if(ord == 1) {
        for(int i = 0; i <= n%10; ++i) res[i] = 1;
        return res;
    }
    const Tag tag(n, ord, top);
    if(memo.count(tag) > 0) return memo[tag];
    const int d = (n/ord)%10;

    for(int digit = 0; digit < d; ++digit) {
        bool istop = top && (digit == 0);
        const vector<int> rem = rec(ord-1, ord/10, istop);
        for(int i = 0; i <= 9; ++i) {
            res[i] += rem[i];
        }
        //cout << top << endl;
        if(!istop) {
            res[digit] += ord;
        }
        //cout << n << ':' << digit << ' ' << res << endl;
    }

    // count for a****
    {
        const vector<int> v = rec(n%ord, ord/10, top && d==0);
        //cout << n%ord << "@" << (top&&d==0) << "@" << ord/10 << v << endl;
        for(int digit = 0; digit <= 9; ++digit) {
            res[digit] += v[digit];
        }
        if(d > 0 || !top) res[d] += n%ord + 1;
    }
    //cout << "res " << n << ':' << top << ':' << ord << ' ' << res << endl;
    return memo[tag] = res;
}

int main() {
    ios::sync_with_stdio(0);

    //cout << rec(999, 100, true) << endl;
    //cout << rec(1000, 1000, true) << endl;
    while(true) {
        int A, B;
        cin >> A >> B;
        if(!A && !B) break;
        if(A > B) swap(A, B);

        A--;
        int aord = (int)pow(10, A==0 ? 0 : (int)log10(A));
        int bord = (int)pow(10, (int)log10(B));
        vector<int> acnt = rec(A, aord, true); 
        vector<int> bcnt = rec(B, bord, true);
        for(int digit = 0; digit <= 9; ++digit) {
            if(digit != 0) cout << ' ';
            cout << bcnt[digit] - acnt[digit];
        }
        cout << endl;
    }

    return 0;
}
