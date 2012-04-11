//Name: Single-Player Games
//Level: 3
//Category: 構文解析,行列,方程式
//Node:

/*
 * それぞれの木について，他の木を変数にした方程式が立てられる．
 * これを適当な手段で解けばよい．
 * ちなみにGaussian Eliminationで毎回正規化してたら誤差死した．
 */
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <cstdio>

using namespace std;

typedef string::iterator Iterator;

const double EPS = 1e-10;

enum TreeType {
    TREE_IDENT,
    TREE_INTEGER,
    TREE_TREE,
};

struct Tree {
    enum TreeType type;
    char ident;
    int val;
    vector<Tree*> children;
};

void skipwhite(Iterator &it) {
    while(isspace(*it)) {
        ++it;
    }
}

void skip(Iterator &it, char ch) {
    skipwhite(it);
    if(*it != ch) {
        cerr << "expected " << ch << " but " << *it << endl;
        abort();
    }
    ++it;
    skipwhite(it);
}

Tree* ident(Iterator &it) {
    Tree *res = new Tree;
    res->type = TREE_IDENT;
    res->ident = *it;

    skip(it, *it);
    return res;
}

Tree* integer(Iterator &it) {
    Tree *res;
    if(*it == '-') {
        ++it;
        res = integer(it);
        res->val *= -1;
    }
    else {
        res = new Tree;
        res->type = TREE_INTEGER;
        res->val = 0;
        while(isdigit(*it)) {
            res->val *= 10;
            res->val += *it - '0';
            ++it;
        }
    }
    skipwhite(it);
    return res;
}

Tree* realtree(Iterator&);

Tree* tree(Iterator &it) {
    if(islower(*it)) {
        return ident(it);
    }
    else if(isdigit(*it) || *it == '-') {
        return integer(it);
    }
    else {
        return realtree(it);
    }
}
        
Tree* realtree(Iterator &it) {
    Tree *res = new Tree;
    res->type = TREE_TREE;
    res->children.clear();

    skip(it, '(');
    while(*it != ')') {
        res->children.push_back(tree(it));
        skipwhite(it);
    }
    skip(it, ')');
    return res;
}

pair<Tree*,Tree*> def(Iterator &it) {
    Tree *id = ident(it);
    skip(it, '=');
    Tree *t = realtree(it);
    return make_pair(id, t);
}

int N;
void traverse(int idx, Tree *tree, double prob, vector<vector<double> > &matrix) {
    if(tree->type == TREE_TREE) {
        for(vector<Tree*>::iterator it = tree->children.begin(); it != tree->children.end(); ++it) {
            traverse(idx, *it, prob/tree->children.size(), matrix);
        }
    }
    else if(tree->type == TREE_IDENT) {
        matrix[idx][tree->ident-'a'] += prob;
    }
    else if(tree->type == TREE_INTEGER) {
        matrix[idx][N] += tree->val * prob;
    }
}

int main() {
    ios::sync_with_stdio(0);

    for(int GAME = 1; ; ++GAME) {
        cin >> N;
        cin.ignore();
        if(!N) break;

        vector<vector<double> > matrix(N, vector<double>(N+1, 0));
        for(int i = 0; i < N; ++i) {
            string str;
            getline(cin, str);
            Iterator it = str.begin();
            pair<Tree*,Tree*> res = def(it);

            int idx = res.first->ident-'a';
            traverse(idx, res.second, 1.0, matrix);
            matrix[idx][idx] += -1;
        }

        /*
        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < N+1; ++c) {
                cout << matrix[r][c] << ' ';
            }
            cout << endl;
        }
        */

        // Gaussian Elimination
        for(int r = 0; r < N; ++r) {
            double pivot = matrix[r][r];
            if(fabs(pivot) < EPS) {
                continue;
            }

            for(int rr = 0; rr < N; ++rr) {
                if(r == rr) continue;
                double a = matrix[rr][r];
                for(int c = 0; c < N+1; ++c) {
                    matrix[rr][c] -= matrix[r][c]*a/matrix[r][r];
                }
            }

            /*
            for(int rr = 0; rr < N; ++rr) {
                for(int c = 0; c < N+1; ++c) {
                    cout << matrix[rr][c] << ' ';
                }
                cout << endl;
            }
            */
        }

        vector<double> ans(N);
        for(int r = 0; r < N; ++r) {
            bool ok = true;
            for(int c = 0; c < N; ++c) {
                if(c != r && fabs(matrix[r][c]) > EPS) {
                    ok = false;
                    break;
                }
            }
            ok &= fabs(matrix[r][r]) > EPS;
            if(ok) {
                ans[r] = -matrix[r][N] / matrix[r][r];
            }
            else {
                ans[r] = 0.0/0.0;
            }
        }
        
        cout.precision(3);
        cout.setf(ios::fixed);
        cout << "Game " << GAME << endl;
        for(int i = 0; i < N; ++i) {
            cout << "Expected score for " << char(i+'a');
            if(isnan(ans[i])) {
                cout << " undefined";
            }
            else {
                cout << " = " << ans[i];
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
