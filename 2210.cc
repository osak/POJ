//Name: Metric Time
//Level: 2
//Category: 実装,日付
//Note:

/*
 * 単位変換やるだけ．
 * うるう年の数はたぶんO(1)で求められるけど，範囲が狭いしリストで持っておいてupper_boundを使うのが確実．
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long SEC_PER_MIN = 60;
const long long SEC_PER_HOUR = SEC_PER_MIN*60;
const long long SEC_PER_DAY = SEC_PER_HOUR*24;
const long long SEC_PER_YEAR = SEC_PER_DAY*365;

const int DAY_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<int> leapyear_list;

inline bool leapyear(int i) {
    return (i%400 == 0) || (i%4 == 0 && i%100 != 0);
}

int leapyears(int year) {
    vector<int>::iterator it = upper_bound(leapyear_list.begin(), leapyear_list.end(), year);
    return it-leapyear_list.begin();
    int cnt = 0;
    for(int i = 2000; i <= year; i += 4) {
        if(leapyear(i)) ++cnt;
    }
    return cnt;
}

int days_till_month(int month, int year) {
    int res = 0;
    for(int i = 1; i < month; ++i) {
        res += DAY_IN_MONTH[i];
        if(leapyear(year) && i == 2) ++res;
    }
    return res;
}

void metric_time(int h, int m, int s, int &mh, int &mm, int &ms) {
    static const int SECS_IN_DAY = 60*60*24;
    static const int SECS_IN_METRIC_DAY = 100*100*10;
    int sec = h*3600+m*60+s;
    int msec = (long long)sec*SECS_IN_METRIC_DAY / SECS_IN_DAY;

    ms = msec % 100;
    msec /= 100;
    mm = msec % 100;
    msec /= 100;
    mh = msec;
}

void metric_date(int day, int month, int year, int &mday, int &mmonth, int &myear) {
    static const int DAYS_IN_METRIC_YEAR = 10*10*10;
    int days = 365*(year-2000) + days_till_month(month, year) + day-1;
    days += leapyears(year-1);

    mday = days % 100 + 1;
    days /= 100;
    mmonth = days % 10 + 1;
    days /= 10;
    myear = days;
}

int main() {
    ios::sync_with_stdio(0);

    for(int i = 2000; i <= 50000; ++i) {
        if(leapyear(i)) leapyear_list.push_back(i);
    }
    int N;
    cin >> N;
    while(N--) {
        string t, d;
        cin >> t >> d;
        for(int i = 0; i < t.size(); ++i)
            if(t[i] == ':') t[i] = ' ';
        for(int i = 0; i < d.size(); ++i)
            if(d[i] == '.') d[i] = ' ';

        int h, m, s;
        {
            istringstream is(t);
            is >> h >> m >> s;
        }

        int day, month, year;
        {
            istringstream is(d);
            is >> day >> month >> year;
        }

        int mh, mm, ms;
        metric_time(h, m, s, mh, mm, ms);

        int mday, mmonth, myear;
        metric_date(day, month, year, mday, mmonth, myear);
        cout << mh << ':' << mm << ':' << ms << ' ' << mday << '.' << mmonth << '.' << myear << endl;
    }

    return 0;
}
