//Name: FILE MAPPING
//Level: 1
//Category: 木構造,再帰
//Note: 問題が不親切。ファイル名だけソートが必要

/*
 * 木構造をシミュレートしていくだけ。
 * 問題文が不親切だが、ディレクトリは出現順、ファイル名はソートして出力する。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Dir {
    string name;
    Dir *parent;
    vector<Dir*> dirs;
    vector<string> files;
};

void print_dir(Dir *dir, string prefix) {
    cout << prefix << dir->name << endl;
    if(dir->dirs.size() > 0) 
        for(int i = 0; i < dir->dirs.size(); ++i) print_dir(dir->dirs[i], prefix + "|     ");
    sort(dir->files.begin(), dir->files.end());
    for(int i = 0; i < dir->files.size(); ++i) cout << prefix << dir->files[i] << endl;
}

int main() {
    for(int C = 1; ; ++C) {
        Dir *root = new Dir;
        root->name = "ROOT";

        Dir *curdir = root;
        while(true) {
            string name;
            cin >> name;
            if(name[0] == 'f') curdir->files.push_back(name);
            else if(name[0] == 'd') {
                Dir *d = new Dir;
                d->name = name;
                d->parent = curdir;
                curdir->dirs.push_back(d);
                curdir = d;
            }
            else if(name == "]") curdir = curdir->parent;
            else if(name == "*") break;
            else if(name == "#") return 0;
        }

        cout << "DATA SET " << C << ":" << endl;
        print_dir(root, "");
        cout << endl;
    }

    return 0;
}
