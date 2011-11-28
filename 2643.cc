#include <iostream>
#include <string>
#include <map>

using namespace std;

int cnt[10001];

int main() {
    map<string, string> candidate2party;
    map<string, int> getvote;

    int n;
    cin >> n;
    cin.ignore();
    while(n--) {
        string name, party;
        getline(cin, name);
        getline(cin, party);
        candidate2party[name] = party;
    }
    int m;
    cin >> m;
    cin.ignore();
    while(m--) {
        string name;
        getline(cin, name);
        getvote[name]++;
    }

    int maxvote = 0;
    string winner;
    for(map<string,int>::iterator it = getvote.begin(); it != getvote.end(); it++) {
        if((*it).second > maxvote) {
            winner = (*it).first;
            maxvote = (*it).second;
        }
        cnt[(*it).second]++;
    }
    if(cnt[maxvote] > 1) {
        cout << "tie" << endl;
    }
    else {
        cout << candidate2party[winner] << endl;
    }

    return 0;
}

