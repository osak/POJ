//Name: Complicated Expressions
//Level: 3
//Category: 構文解析
//Note: TLE厳しい

/* 解法：
 * とりあえず構文解析してから()の位置を考える．
 * 優先順位の逆転があるときと，-や/が絡んで左結合されてはまずいときのみに()がつく．
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum AST_Type {
    TYPE_OPERATOR,
    TYPE_IDENTIFIER,
};

struct AST {
    AST_Type type;
    string name;
    char op;
    AST *left, *right;

    AST() {}
    AST(char op) : type(TYPE_OPERATOR), op(op) {}
    AST(const string &name) : type(TYPE_IDENTIFIER), name(name) {}
} buf[250];

typedef string::iterator Iterator;

int bufpos = 0;
AST *fetch(char op) {
    return &(buf[bufpos++] = AST(op));
}
AST *fetch(const string &name) {
    return &(buf[bufpos++] = AST(name));
}

void skip(const string &str, int &pos, char c) {
    if(str[pos] != c) {
        cerr << "expected " << c << " but " << str[pos] << " near " << str.substr(pos) << endl;
    }
    ++pos;
}

string identifier(const string &str, int &pos) {
    int start = pos;
    while(islower(str[pos])) ++pos;
    return str.substr(start, pos-start);
}

AST* expr(const string &str, int &pos);

AST* term(const string &str, int &pos) {
    AST *cur;
    if(str[pos] == '(') {
        ++pos;
        cur = expr(str, pos);
        skip(str, pos, ')');
    }
    else {
        cur = fetch(identifier(str, pos));
    }
    return cur;
}

AST* factor(const string &str, int &pos) {
    AST *cur = term(str, pos);
    while(str[pos] == '*' || str[pos] == '/') {
        AST *opnode = fetch(str[pos]);
        ++pos;
        opnode->left = cur;
        opnode->right = term(str, pos);
        cur = opnode;
    }
    return cur;
}

AST* expr(const string &str, int &pos) {
    AST *cur = factor(str, pos);
    while(str[pos] == '+' || str[pos] == '-') {
        AST *opnode = fetch(str[pos]);
        ++pos;
        opnode->left = cur;
        opnode->right = factor(str, pos);
        cur = opnode;
    }
    return cur;
}

void print_ast(AST *cur, int depth) {
    for(int i = 0; i < depth; ++i) cout << ' ';
    if(cur->type == TYPE_OPERATOR) cout << cur->op << endl;
    if(cur->type == TYPE_IDENTIFIER) cout << cur->name << endl;
    if(cur->type == TYPE_OPERATOR) {
        print_ast(cur->left, depth+2);
        print_ast(cur->right, depth+2);
    }
}

string visit(AST *cur, char prev, bool rhs) {
    if(cur->type == TYPE_IDENTIFIER) return cur->name;

    if(cur->type == TYPE_OPERATOR) {
        bool need_paren;
        if(cur->op == '+' || cur->op == '-') {
            need_paren = prev == '*' || prev == '/';
            if(rhs && prev == '-') need_paren = true;
        }
        else {
            need_paren = (rhs && prev == '/');
        }
        string lhs = visit(cur->left, cur->op, false);
        string rhs = visit(cur->right, cur->op, true);
        if(need_paren) return string("(") + lhs + cur->op + rhs + ")";
        else return lhs + cur->op + rhs;
    }
    return "";
}

void free_ast(AST *cur) {
    if(cur->type == TYPE_IDENTIFIER) delete cur;
    else {
        free_ast(cur->left);
        free_ast(cur->right);
        delete cur;
    }
}

int main() {
    int N;
    cin >> N;
    while(N--) {
        bufpos = 0;
        string str;
        cin >> str;
        int pos = 0;
        AST *ast = expr(str, pos);
        string expr = visit(ast, '\0', false);
        cout << expr << endl;
    }

    return 0;
}
