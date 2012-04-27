//Name: Apply a Cold Compress
//Level: 3
//Category: 実装,構文木
//Note:

/*
 * 命令の木を作り，下から順に組み立てながらそれぞれの命令が占有する幅と高さを求める．
 * 01,10で左右を併合するときは，問題文にあるようにスケールを逓倍して辺の長さを揃えてから
 * もう片方の辺の長さを合計する．
 * 領域の大きさが分かったら，あとは実際に組み立てればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

inline int lcm(int a, int b) {
    return a*b / gcd(a,b);
}

enum Type { TYPE_BLACK, TYPE_VERTICAL, TYPE_HORIZONTAL, TYPE_WHITE };
struct Command {
    int w, h;
    Type type;
    Command *lhs, *rhs;

    Command(Type type) : type(type) {
        if(type == TYPE_BLACK || type == TYPE_WHITE) {
            w = h = 1;
        }
        else {
            w = h = 0;
        }
    }

    Command(Type type, Command *lhs, Command *rhs) : 
        type(type), lhs(lhs), rhs(rhs)
    {
        if(type == TYPE_VERTICAL) {
            int neww = lcm(lhs->w, rhs->w);
            lhs->scale(neww / lhs->w);
            rhs->scale(neww / rhs->w);
            w = neww;
            h = lhs->h + rhs->h;

        }
        else if(type == TYPE_HORIZONTAL) {
            int newh = lcm(lhs->h, rhs->h);
            lhs->scale(newh / lhs->h);
            rhs->scale(newh / rhs->h);
            w = lhs->w + rhs->w;
            h = newh;
        }
    }

    ~Command() {
        if(type == TYPE_VERTICAL || type == TYPE_HORIZONTAL) {
            delete lhs;
            delete rhs;
        }
    }

    void scale(int a) {
        w *= a;
        h *= a;
        if(type == TYPE_VERTICAL || type == TYPE_HORIZONTAL) {
            lhs->scale(a);
            rhs->scale(a);
        }
    }

    void paint(vector<vector<char> > &field, int x, int y) {
        switch(type) {
            case TYPE_BLACK:
                for(int i = 0; i < h; ++i) {
                    for(int j = 0; j < w; ++j) {
                        field[y+i][x+j] = 'X';
                    }
                }
                break;
            case TYPE_VERTICAL:
                lhs->paint(field, x, y);
                rhs->paint(field, x, y+lhs->h);
                break;
            case TYPE_HORIZONTAL:
                lhs->paint(field, x, y);
                rhs->paint(field, x+lhs->w, y);
                break;
            case TYPE_WHITE:
                break;
        }
    }
};

Command* parse(string::iterator &it) {
    int t = (*it++-'0')*2;
    t += *it++-'0';

    if(t == TYPE_BLACK || t == TYPE_WHITE) {
        return new Command((Type)t);
    }
    else {
        Command *lhs = parse(it);
        Command *rhs = parse(it);
        return new Command((Type)t, lhs, rhs);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string line;
    while(getline(cin, line)) {
        string::iterator it = line.begin();
        Command *root = parse(it);

        vector<vector<char> > field(root->h, vector<char>(root->w, ' '));
        root->paint(field, 0, 0);

        for(int i = 0; i < root->w+2; ++i) {
            cout << '-';
        }
        cout << endl;
        for(int y = 0; y < root->h; ++y) {
            cout << '|';
            for(int x = 0; x < root->w; ++x) {
                cout << field[y][x];
            }
            cout << '|' << endl;
        }
        for(int i = 0; i < root->w+2; ++i) {
            cout << '-';
        }
        cout << endl;

        delete root;
    }
    return 0;
}
