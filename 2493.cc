#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

typedef unsigned char byte;

char buf[10001];

int main() {
    int N;
    cin >> N;
    for(int sc = 1; sc <= N; ++sc) {
        map<string, int> counts;
        int n;
        cin >> n;

        /*
        for(int i = 0; i < 57; ++i) {
            for(int j = 0; j < 57; ++j) {
                counts[i][j].clear();
            }
        }
        */
        for(int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            if(str.size() > 3) {
                sort(str.begin()+1, str.end()-1);
            }
            counts[str]++;
        }

        cout << "Scenario #" << sc << ":" << endl;
        int m;
        cin >> m;
        fgets(buf, 10000, stdin); //Avoid newline
        for(int i = 0; i < m; ++i) {
            int result = 1;
            fgets(buf, 10001, stdin);
            for(char *ptr = strtok(buf, " \n"); ptr; ptr = strtok(NULL, " \n")) {
                string str(ptr);
                if(str.size() > 3) {
                    sort(str.begin()+1, str.end()-1);
                }
                int count = counts[str];
                result *= count;
            }
            cout << result << endl;
        }
        cout << endl;
    }

    return 0;
}
