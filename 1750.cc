//Name: Dictionary
//Level: 2
//Cateogry: 文字列
//Note: TLEがかなり厳しい

/*
 * 直前の文字列と先頭の何文字が一致しているかでインデント幅が変わる．
 * インデントが深くなるごとに，さらにインデントするために必要な文字数は増えていく．
 *
 * POJだとかなりTLEが厳しいのでC++で通した．
 */
#include <cstdio>
#include <cctype>
#include <cstring>

int matchcnt(const char *s1, const char *s2) {
    int i;
    for(i = 0; s1[i] && s2[i]; ++i) {
        if(s1[i] != s2[i]) break;
    }
    return i;
}

int main() {
    int prevdepth = 0;
    char buf1[20], buf2[20] = {0};
    char *str = buf1, *prev = buf2;
    char *tmp;

    while(fgets(str, 20, stdin)) {
        int len = strlen(str)-1;
        while(len >= 0 && isspace(str[len])) str[len--] = '\0';
        int match = matchcnt(prev, str);
        int depth = match;
        if(depth > prevdepth+1) depth = prevdepth+1;
        printf("%*s%s\n", depth, "", str);
        tmp = str; str = prev; prev = tmp;
        prevdepth = depth;
    }

    return 0;
}
