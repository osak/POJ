//Name: Snowflake Snow Snowflakes
//Level: 2
//Category: 高速化,順序
//Note: ひどい高速化ゲー

/*
 * vector等を使うと速度的に間に合わない。
 * やること自体は単純で、RotationとReverse12通りの中で辞書順最小のものを選び、
 * sortしてからuniqueするだけ。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdio>

using namespace std;

struct Tag {
    int v[6];
    bool operator < (const Tag &other) const {
        for(int i = 0; i < 6; ++i)
            if(v[i] != other.v[i]) return v[i] < other.v[i];
        return false;
    }

    bool operator == (const Tag &other) const {
        for(int i = 0; i < 6; ++i)
            if(v[i] != other.v[i]) return false;
        return true;
    }
};

//Tag tags[100000];

int main() {
    int N;
    scanf("%d", &N);

    vector<vector<int> > v;
    for(int i = 0; i < N; ++i) {
        vector<int> l(6);
        for(int j = 0; j < 6; ++j) scanf("%d", &l[j]);
        vector<int> best = l;
        for(int j = 0; j < 6; ++j) {
            int fst = l[0];
            for(int k = 0; k < 5; ++k) l[k] = l[k+1];
            l[5] = fst;
            if(l < best) best = l;
        }
        reverse(l.begin(), l.end());
        for(int j = 0; j < 6; ++j) {
            int fst = l[0];
            for(int k = 0; k < 5; ++k) l[k] = l[k+1];
            l[5] = fst;
            if(l < best) best = l;
        }
        v.push_back(best);
    }
    sort(v.begin(), v.end());
    bool found = false;
    for(int i = 1; i < N; ++i) {
        if(v[i-1] == v[i]) found = true;
    }
    
    cout << (found?"Twin snowflakes found.":"No two snowflakes are alike.") << endl;
    return 0;
}
