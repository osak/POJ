//Name: The Finite State Text-Processing
//Level: 2
//Category: 実装
//Note:

/*
 * ひとつの状態はエッジの集合なので，ナイーブにmapで管理する．
 * あとはがんばる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

const int INPUT_ANY = 256;

struct State {
    map<int, pair<string,string> > trans;
};

string& replace_bs(string &str, char c_char) {
    for(string::iterator it = str.begin(); it != str.end(); ++it) {
        if(*it == '\\') {
            it = str.erase(it);
            if(*it == 'b') *it = ' ';
            else if(*it == 'n') *it = '\n';
            else if(*it == 'c') *it = c_char;
            else if(*it == '\\') *it = '\\';
        }
    }
    return str;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int CNT = 1; ; ++CNT) {
        int N;
        cin >> N;
        if(!N) break;

        map<string, State> states;
        while(N--) {
            string name;
            int transnum;
            cin >> name >> transnum;
            while(transnum--) {
                string input, next, output;
                cin >> input >> next >> output;
                for(string::iterator it = input.begin(); it != input.end(); ++it) {
                    int val = *it;
                    if(*it == '\\') {
                        ++it;
                        if(*it == 'n') val = '\n';
                        else if(*it == 'b') val = ' ';
                        else if(*it == '\\') val = '\\';
                        else if(*it == 'c') val = INPUT_ANY;
                    }
                    states[name].trans[val] = make_pair(next, output);
                }
            }
        }

        cout << "Finite State Machine " << CNT << ":" << endl;
        cin.ignore(100, '\n');
        string curstate = "START";
        string buf = "";
        string::iterator it = buf.end();
        while(curstate != "END") {
            if(it == buf.end()) {
                getline(cin, buf);
                buf += "\n";
                it = buf.begin();
            }

            State &state = states[curstate];
            pair<string,string> trans;
            if(state.trans.count(*it) > 0) {
                trans = state.trans[*it];
            }
            else {
                trans = state.trans[INPUT_ANY];
            }
            string output = trans.second;
            if(output == "\\0") output = "";
            replace_bs(output, *it);
            cout << output;

            curstate = trans.first;
            ++it;
        }
    }

    return 0;
}
