//Name: Hire and Fire
//Level: 3
//Category: シミュレーション,木構造,tree
//Note:

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>
#include <map>
#include <string>

using namespace std;

class Member {
    string name;
    deque<Member*> children;
    Member *parent;

public:
    static Member *CEO;

    Member() : parent(NULL) {}
    Member(const string &n) : name(n), parent(NULL) {}

    void print(int level = 0) const {
        for(int i = 0; i < level; ++i) cout << '+';
        cout << name << endl;
        for(int i = 0; i < children.size(); ++i) {
            children[i]->print(level+1);
        }
    }

    void addChild(Member *m) {
        children.push_back(m);
        m->setParent(this);
    }

    void setParent(Member *m) {
        parent = m;
        if(m == NULL) Member::CEO = this;
    }

    void substitute(Member *old, Member *neu) {
        for(int i = 0; i < children.size(); ++i) {
            if(children[i] == old) {
                children[i] = neu;
                neu->setParent(this);
                break;
            }
        }
    }

    void rotate() {
        if(children.size() == 0) return;

        Member *newtop = children[0];
        children.pop_front();
        newtop->rotate();
        newtop->inherit(children);

        children.clear();
        children.push_back(newtop);
    }

    void inherit(const deque<Member*> &v) {
        children.insert(children.end(), v.begin(), v.end());
        for(int i = 0; i < children.size(); ++i) {
            children[i]->setParent(this);
        }
    }

    void fireMe() {
        rotate();
        for(int i = 0; i < children.size(); ++i) {
            children[i]->setParent(this->parent);
        }
        if(parent) {
            if(children.size() > 0) {
                parent->substitute(this, children[0]);
            }
            else {
                parent->remove(this);
            }
        }
    }

    void remove(Member *m) {
        for(deque<Member*>::iterator it = children.begin(); it != children.end(); ++it) {
            if(*it == m) {
                children.erase(it);
                break;
            }
        }
    }
};


Member* Member::CEO = NULL;

int main() {
    ios::sync_with_stdio(0);

    map<string, Member*> gtbl;
    string s1, s2, s3;

    //Root
    {
        cin >> s1;
        Member *m = new Member(s1);
        m->setParent(NULL); //Be root
        gtbl[s1] = m;
    }
    while(cin >> s1) {
        if(s1 == "print") {
            Member::CEO->print();
            for(int i = 0; i < 60; ++i) cout << '-';
            cout << endl;
        }
        else if(s1 == "fire") {
            cin >> s2;
            gtbl[s2]->fireMe();
            delete gtbl[s2];
            gtbl.erase(s2);
        }
        else {
            cin >> s2 >> s3;
            Member *m = new Member(s3);
            gtbl[s3] = m;
            gtbl[s1]->addChild(m);
        }
    }

    return 0;
}
