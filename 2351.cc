//Name: Time Zones
//Level: 2
//Category: 実装,時刻
//Note:

/*
 * 時刻変換やるだけ．
 * 24時間制における0時*分は12:** a.m，12時*分は12:** p.mとなることに注意．
 */
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct TimeZone {
    int diff;
    bool half;

    TimeZone() {}
    TimeZone(int d, bool h) : diff(d), half(h) {}

    int normalize(int t) const {
        if(t < 0) return t + 24*60;
        if(t >= 24*60) return t % (24*60);
        return t;
    }

    int local_to_utc(int t) const {
        int ans = t - diff*60;
        if(half) {
            if(diff > 0) ans -= 30;
            else ans += 30;
        }
        return normalize(ans);
    }

    int utc_to_local(int t) const {
        int ans = t + diff*60;
        if(half) {
            if(diff > 0) ans += 30;
            else ans -= 30;
        }
        return normalize(ans);
    }
};

int parse(string t, string ampm) {
    if(t == "noon") return 12*60;
    if(t == "midnight") return 0;

    int colon = t.find(':');
    int hour = atoi(t.substr(0, colon).c_str());
    int minute = atoi(t.substr(colon+1).c_str());
    if(hour == 12) hour = 0;
    if(ampm == "p.m.") hour += 12;

    return hour*60 + minute;
}

void format_out(int t) {
    if(t == 12*60) cout << "noon" << endl;
    else if(t == 0) cout << "midnight" << endl;
    else {
        string ampm = "a.m.";
        int hour = t / 60;
        if(hour >= 12) {
            hour -= 12;
            ampm = "p.m.";
        }
        if(hour == 0) {
            hour += 12;
        }
        int minute = t % 60;
        printf("%d:%02d %s\n", hour, minute, ampm.c_str());
    }
}

int main() {
    map<string,TimeZone> tz;
    tz["UTC"] = TimeZone(0, false);
    tz["GMT"] = TimeZone(0, false);
    tz["BST"] = TimeZone(+1, false);
    tz["IST"] = TimeZone(+1, false);
    tz["WET"] = TimeZone(0, false);
    tz["WEST"] = TimeZone(+1, false);
    tz["CET"] = TimeZone(+1, false);
    tz["CEST"] = TimeZone(+2, false);
    tz["EET"] = TimeZone(+2, false);
    tz["EEST"] = TimeZone(+3, false);
    tz["MSK"] = TimeZone(+3, false);
    tz["MSD"] = TimeZone(+4, false);
    tz["AST"] = TimeZone(-4, false);
    tz["ADT"] = TimeZone(-3, false);
    tz["NST"] = TimeZone(-3, true);
    tz["NDT"] = TimeZone(-2, true);
    tz["EST"] = TimeZone(-5, false);
    tz["EDT"] = TimeZone(-4, false);
    tz["CST"] = TimeZone(-6, false);
    tz["CDT"] = TimeZone(-5, false);
    tz["MST"] = TimeZone(-7, false);
    tz["MDT"] = TimeZone(-6, false);
    tz["PST"] = TimeZone(-8, false);
    tz["PDT"] = TimeZone(-7, false);
    tz["HST"] = TimeZone(-10, false);
    tz["AKST"] = TimeZone(-9, false);
    tz["AKDT"] = TimeZone(-8, false);
    tz["AEST"] = TimeZone(+10, false);
    tz["AEDT"] = TimeZone(+11, false);
    tz["ACST"] = TimeZone(+9, true);
    tz["ACDT"] = TimeZone(+10, true);
    tz["AWST"] = TimeZone(+8, false);

    int N;
    cin >> N;
    while(N--) {
        string t, ampm;
        cin >> t;
        if(t != "noon" && t != "midnight") {
            cin >> ampm;
        }
        int cur = parse(t, ampm);

        string from, to;
        cin >> from >> to;
        format_out(tz[to].utc_to_local(tz[from].local_to_utc(cur)));
    }

    return 0;
}
