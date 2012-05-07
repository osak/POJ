//Name: Calendar Game
//Level: 2
//Category: カレンダー,DP
//Note:

/*
 * 特定の日がAdamの手番で回ってきたときに勝てるかを考える．
 * (1) 2001/11/4が回ってきたら負け(Eveが先に到達したことを意味する)．
 * (2) 1手で2001/11/4に到達できる日付なら勝ち．
 * (3-1) (2)の日付にしか行けないなら負け(Eveが必勝の日付を手に入れるから)．
 * (3-2) (2)の日付に行く方法が存在するなら勝ち．
 *
 * 日付は高々102年分しかないので，2001/11/4から逆向きにナイーブにDPすればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int DAYS[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap(int year) {
    if(year % 4 != 0) return false;
    if(year % 100 != 0) return true;
    if(year % 400 == 0) return true;
    return false;
}

bool in_range(int a, int x, int b) {
    return a <= x && x <= b;
}

bool is_valid(int year, int month, int day) {
    if(!in_range(1, month, 12)) return false;
    int days = DAYS[month];
    if(month == 2 && is_leap(year)) days = 29;
    return in_range(1, day, days);
}

struct Day {
    int year, month, day;

    Day(int y, int m, int d) : year(y), month(m), day(d) {}

    Day prev_day() const {
        int nd = day - 1;
        int nm = month;
        int ny = year;
        if(nd == 0) {
            --nm;
            if(nm == 0) {
                --ny;
                nm = 12;
            }
            nd = DAYS[nm];
            if(nm == 2 && is_leap(ny)) nd = 29;
        }
        return Day(ny, nm, nd);
    }

    Day prev_month() const {
        int nd = day;
        int nm = month - 1;
        int ny = year;
        if(nm == 0) {
            --ny;
            nm = 12;
        }
        if(!is_valid(ny, nm, nd)) ny = 0;
        return Day(ny, nm, nd);
    }

    bool operator ==(const Day &other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator !=(const Day &other) const {
        return !(*this == other);
    }
};

void update(bool &a, bool val) {
    if(!a) a = val;
}

//win[year-1900][month][day]
bool win[102][13][32];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int y, m, d;
        cin >> y >> m >> d;
        memset(win, 0, sizeof(win));
        Day last(y, m, d);

        Day cur(2001, 11, 4);
        win[cur.year-1900][cur.month][cur.day] = false;
        while(cur != last) {
            Day prev = cur.prev_day();
            update(win[prev.year-1900][prev.month][prev.day], !win[cur.year-1900][cur.month][cur.day]);
            prev = cur.prev_month();
            if(prev.year != 0 && prev.year >= 1900) {
                update(win[prev.year-1900][prev.month][prev.day], !win[cur.year-1900][cur.month][cur.day]);
            }
            cur = cur.prev_day();
        }
        cout << (win[y-1900][m][d]?"YES":"NO") << endl;
    }

    return 0;
}
