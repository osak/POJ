//Name: Chandelier
//Level: 2
//Category: 探索,Special Judge
//Note:

/*
 * まずシャンデリアを構築し，各シャンデリアについて開始地点を全通り試す．
 * あるシャンデリアを構築するときのスタックの使用量は前の状態に依存しないので，ひとつのシャンデリアの構築手順は
 * キャッシュしておくことができる．
 *
 * 全てのノードで最適なプログラムまで保存しているせいか，G++だとMLEしてしまった．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <cassert>

using namespace std;

enum Type { TYPE_RING, TYPE_PENDANT };

struct Chandelier {
    Type type;
    vector<Chandelier*> children;
    struct {
        int depth;
        string prog;
        bool valid;
    } cache;

    Chandelier() : type(TYPE_PENDANT) {
        cache.valid = false;
    }

    void optimize() {
        if(cache.valid) return;

        if(type == TYPE_PENDANT) {
            cache.depth = 1;
            cache.prog = "a";
        }
        else {
            cache.depth = 20000;
            int N = children.size();
            for(int start = 0; start < N; ++start) {
                int depth = 0;
                string prog = "";
                for(int i = 0; i < N; ++i) {
                    int idx = (start+i) % N;
                    children[idx]->optimize();
                    depth = max(depth, i + children[idx]->cache.depth);
                    prog += children[idx]->cache.prog;
                }
                prog += '0'+N;
                if(depth < cache.depth) {
                    cache.depth = depth;
                    cache.prog = prog;
                }
            }
        }
        cache.valid = true;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string str;
    getline(cin, str);

    stack<Chandelier*> stk;
    for(string::iterator it = str.begin(); it != str.end(); ++it) {
        if(*it == 'a') {
            stk.push(new Chandelier);
        }
        else {
            int n = (*it) - '0';
            Chandelier *ring = new Chandelier();
            ring->type = TYPE_RING;
            while(n--) {
                ring->children.push_back(stk.top());
                stk.pop();
            }
            // スタックマシン上でコンパイルするので、逆順にトラバースする必要があるため
            reverse(ring->children.begin(), ring->children.end());
            stk.push(ring);
        }
    }
    assert(stk.size() == 1);
    Chandelier *root = stk.top();
    root->optimize();

    cout << root->cache.depth << endl;
    cout << root->cache.prog << endl;

    return 0;
}
