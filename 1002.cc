//Name: 487-3279
//Level: 2
//Category: 文字列,数え上げ,やるだけ
//Note: 速度が結構シビアなのでG++ではなくC++でSubmitするとよい

/*
 * ハイフンを無視しながら数字だけの表記に直していき、mapで個数を数える。
 * G++のSTLだと速度的に間に合わないっぽいのでC++でコンパイルした。
 */
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <cctype>

using namespace std;

int main() {
    int N;
    scanf("%d ", &N);

    map<string, int> m;
    const char *enc = "22233344455566677778889999";
    while(N--) {
        char buf[256];
        char phone[9] = {0};
        fgets(buf, 256, stdin);

        int pos = 0;
        for(int i = 0; buf[i]; ++i) {
            if(buf[i] == '-') continue;
            if(buf[i] == 'Q' || buf[i] == 'Z') continue;
            if(isupper(buf[i])) phone[pos++] = enc[buf[i]-'A'];
            else if(isdigit(buf[i])) phone[pos++] = buf[i];

            if(pos == 3) phone[pos++] = '-';
        }
        m[string(phone)]++;
    }

    bool nodup = true;
    for(map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
        if(it->second >= 2) {
            printf("%s %d\n", it->first.c_str(), it->second);
            nodup = false;
        }
    }
    if(nodup) puts("No duplicates.");

    return 0;
}

