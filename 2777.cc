//Name: Count Color
//Level: 3
//Category: SegmentTree
//Note:

/*
 * どの色が塗られているかをbitで管理し，SegmentTreeでクエリを処理する．
 * 塗るときはなるべく大きいセグメントで受けとめておく．
 * 結果を取得するときは，一色のノードにぶつかったらその色を返す．
 * (あるノードが一色→過去に一色で塗られた or 下にその色のノードしかない)
 * 一色のノードの下にあるノードは更新されないまま残ってしまっているが，
 * 更新はそれらのノードに対する塗りが発生するまで遅延させてよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int LEAVES = 131072; //2^17
struct SegmentTree {
    int nodes[LEAVES*2];

    SegmentTree() {
        memset(nodes, 0, sizeof(nodes));
    }

    // [left, right)に対するクエリ．
    // 現在のノードはposで，[pl, pr)を管理する．
    int get_inner(int left, int right, int pos, int pl, int pr) {
        if(pr <= left || right <= pl) return 0; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos]; // ノードがクエリに完全に含まれる

        // 一色の場合，過去に一色塗りされている．
        if(__builtin_popcount(nodes[pos]) == 1) return nodes[pos];

        int lm = get_inner(left, right, pos*2+1, pl, (pl+pr)/2);
        int lr = get_inner(left, right, pos*2+2, (pl+pr)/2, pr);
        return lm | lr;
    }

    // [left, right)に対するクエリ
    int get(int left, int right) {
        return __builtin_popcount(get_inner(left, right, 0, 0, LEAVES));
    }

    int set_inner(int left, int right, int pos, int pl, int pr, int mask) {
        if(pr <= left || right <= pl) return nodes[pos];
        if(left <= pl && pr <= right) return nodes[pos] = mask;

        // 一色の場合，過去に一色塗りされた可能性があるので
        // 下のノードに伝搬させる．
        if(__builtin_popcount(nodes[pos]) == 1) {
            nodes[pos*2+1] = nodes[pos*2+2] = nodes[pos];
        }

        int lm = set_inner(left, right, pos*2+1, pl, (pl+pr)/2, mask);
        int rm = set_inner(left, right, pos*2+2, (pl+pr)/2, pr, mask);
        return nodes[pos] = lm | rm;
    }

    int set(int left, int right, int val) {
        return set_inner(left, right, 0, 0, LEAVES, (1<<val));
    }
} tree;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int L, T, O;
    scanf("%d %d %d", &L, &T, &O);

    tree.set(0, L, 0);
    while(O--) {
        char c;
        scanf(" %c", &c);
        if(c == 'C') {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            a--; b--; c--;
            if(a > b) swap(a, b);
            tree.set(a, b+1, c);
        }
        else if(c == 'P') {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            if(a > b) swap(a, b);
            printf("%d\n", tree.get(a, b+1));
        }
    }

    return 0;
}
