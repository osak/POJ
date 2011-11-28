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

Tag tags[100000];

int main() {
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; ++i) {
        Tag t;
        for(int j = 0; j < 6; ++j) scanf("%d", &t.v[j]);
        Tag best = t;
        for(int j = 0; j < 6; ++j) {
            int fst = t.v[0];
            for(int k = 0; k < 5; ++k) t.v[k] = t.v[k+1];
            t.v[5] = fst;
            if(t < best) best = t;
        }
        reverse(t.v, &t.v[6]);
        for(int j = 0; j < 6; ++j) {
            int fst = t.v[0];
            for(int k = 0; k < 5; ++k) t.v[k] = t.v[k+1];
            t.v[5] = fst;
            if(t < best) best = t;
        }
        tags[i] = best;
    }
    sort(&tags[0], &tags[N]);
    bool found = false;
    for(int i = 1; i < N; ++i) {
        if(tags[i-1] == tags[i]) found = true;
    }
    
    cout << (found?"Twin snowflakes found.":"No two snowflakes are alike.") << endl;
    return 0;
}
