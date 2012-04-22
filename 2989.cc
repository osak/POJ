//Name: All Friends
//Level: 4
//Category: クリーク,DP
//Note:

/*
 * 極大クリーク(maximal clique)を数え上げる．
 *
 * クリーク集合にひとつずつ頂点を加えていく．
 * この頂点とあるクリークについて，
 * ・頂点がクリークに含まれる全ての頂点間に辺を持つとき，そのクリークに含める．
 * ・そうでないときは，頂点とその隣接点からなるクリークが生成できる．
 *   （元がクリークなので，部分集合もクリーク）
 *
 * この実装は非効率なので，POJではC++でないとTLEする．
 */
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

struct Bitset {
    unsigned int bits[4];

    Bitset() {
        bits[0] = bits[1] = bits[2] = bits[3] = 0;
    }

    Bitset(const Bitset &src) {
        memcpy(bits, src.bits, sizeof(bits));
    }

    void insert(int n) {
        bits[n/32] |= 1U<<n%32;
    }

    void remove(int n) {
        bits[n/32] &= ~(1U<<n%32);
    }

    int contains(int n) const {
        return bits[n/32] & (1U<<n%32);
    }

    bool includes(const Bitset &other) const {
#define CHECK(i) ((bits[i]&other.bits[i]) == other.bits[i])
        return CHECK(0) && CHECK(1) && CHECK(2) && CHECK(3);
#undef CHECK
    }

    bool operator ==(const Bitset &other) const {
        return memcmp(bits, other.bits, sizeof(bits)) == 0;
    }

    bool operator !=(const Bitset &other) const {
        return !(*this == other);
    }

    friend Bitset operator &(const Bitset &a, const Bitset &b) {
        Bitset res;
        for(int i = 0; i < 4; ++i) {
            res.bits[i] = a.bits[i] & b.bits[i];
        }
        return res;
    }
};

ostream& operator <<(ostream &o, const Bitset &c) {
    o << '(';
    for(int i = 0; i < 128; ++i) {
        if(c.contains(i)) o << i << ' ';
    }
    o << ')';
    return o;
}

int main() {
    ios::sync_with_stdio(0);
    int N, M;
    while(cin >> N >> M) {
        vector<Bitset> v(N);
        for(int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            v[a].insert(b);
            v[b].insert(a);
        }

        vector<Bitset> cliques;
        {
            Bitset init;
            init.insert(0);
            cliques.push_back(init);
        }
        for(int i = 1; i < N; ++i) {
            vector<Bitset> new_cliques;
            for(vector<Bitset>::iterator it = cliques.begin(); it != cliques.end(); ++it) {
                if(v[i].includes(*it)) {
                    Bitset b = *it;
                    b.insert(i);
                    if(find(new_cliques.begin(), new_cliques.end(), b) == new_cliques.end()) new_cliques.push_back(b);
                }
                else {
                    Bitset b = *it & v[i];
                    b.insert(i);
                    bool valid = true;
                    for(vector<Bitset>::iterator it2 = new_cliques.begin(); it2 != new_cliques.end(); ++it2) {
                        if(it2->includes(b)) {
                            valid = false;
                            break;
                        }
                    }
                    for(int j = 0; j < i; ++j) {
                        if(!b.contains(j) && v[j].includes(b)) {
                            valid = false;
                            break;
                        }
                    }
                    if(valid) new_cliques.push_back(b);
                    new_cliques.push_back(*it);
                }
            }
            cliques.swap(new_cliques);
            /*
            cout << "Step " << i << endl;
            for(vector<Bitset>::iterator it = cliques.begin(); it != cliques.end(); ++it) {
                cout << *it << endl;
            }
            */
            if(cliques.size() > 1000) break;
        }


        if(cliques.size() > 1000) {
            cout << "Too many maximal sets of friends." << endl;
        }
        else {
            cout << cliques.size() << endl;
        }
    }

    return 0;
}
