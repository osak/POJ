//Name: Team Arrangement
//Level: 2
//Category: ソート
//Note:

/*
 * 順番付けの制約から、role順にソートして上から順に選手を選んでいくと良い。
 * 選手をすべて選んだら、その中から一番年数の大きい者を選ぶ。
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define FOREACH(V, E) for(__typeof(E.begin()) V = E.begin(); V != E.end(); ++V)

using namespace std;

struct Player {
    int number;
    string name;
    char role;
    int period;

    Player() : period(0) {}

    bool operator < (const Player &other) const {
        if(role != other.role) return string("GDMS").find(role) < string("GDMS").find(other.role);
        if(number != other.number) return number < other.number;
        return period < other.period;
    }

    bool operator == (const Player &other) const {
        return number == other.number;
    }
};

ostream& operator << (ostream &os, const Player &p) {
    return os << p.number << " " << p.name << " " << p.role;
}

int main() {
    while(true) {
        vector<Player> players;
        for(int i = 0; i < 22; ++i) {
            Player p;
            string years;
            cin >> p.number >> p.name >> p.role;
            getline(cin, years);
            if(p.number == 0) return 0;

            istringstream is(years);
            while(!is.eof()) {
                string str;
                is >> str;
                p.period += atoi(str.substr(5).c_str()) - atoi(str.substr(0, 4).c_str()) + 1;
            }
            players.push_back(p);
        }
        string formation;
        int d, m, s, g;
        cin >> formation;
        d = formation[0]-'0';
        m = formation[2]-'0';
        s = formation[4]-'0';
        g = 1;

        vector<Player> ps;
        sort(players.begin(), players.end());
        FOREACH(it, players) {
            if(it->role == 'D' && d > 0) {
                ps.push_back(*it);
                --d;
            }
            else if(it->role == 'M' && m > 0) {
                ps.push_back(*it);
                --m;
            }
            else if(it->role == 'S' && s > 0) {
                ps.push_back(*it);
                --s;
            }
            else if(it->role == 'G' && g > 0) {
                ps.push_back(*it);
                --g;
            }
        }
        if(d > 0 || m > 0 || s > 0 || g > 0) {
            cout << "IMPOSSIBLE TO ARRANGE" << endl;
        }
        else {
            Player captain = ps[0];
            FOREACH(it, ps) {
                if(it->period > captain.period) captain = *it;
                if(it->period == captain.period && it->number > captain.number) captain = *it;
            }
            cout << captain << endl;
            FOREACH(it, ps) {
                if(*it == captain) continue;
                cout << *it << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
