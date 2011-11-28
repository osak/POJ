//Name: Does This Make Me Look Fat?
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Tag {
    string name;
    int weight;

    bool operator < (const Tag &other) const {
        return weight > other.weight;
    }
};

int main() {
    string tmp;
    bool first = true;
    while(cin >> tmp) {
        vector<Tag> v;

        Tag t;
        while(cin >> t.name) {
            if(t.name == "END") break;
            int day;
            cin >> day >> t.weight;
            t.weight -= day;
            v.push_back(t);
        }

        sort(v.begin(), v.end());
        if(!first) cout << endl;
        for(int i = 0; i < v.size(); ++i) {
            cout << v[i].name << endl;
        }

        first = false;
    }

    return 0;
}
