//Name: Instant Complexity
//Level: 2
//Category: 構文解析,多項式
//Note:

/*
 * 逐次読み込みながら多項式を計算していく．
 * ネストレベルごとに演算バッファを用意することと，Runtimeが0のパターンに注意．
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>

using namespace std;

struct Number {
    bool integer;
    int value;

    Number() {}
    Number(bool b, int v) : integer(b), value(v) {}
};

int main() {
    int N;
    cin >> N;

    for(int CASE = 1; CASE <= N; ++CASE) {
        vector<vector<int> > cnt;
        cnt.push_back(vector<int>(11, 0));
        stack<Number> loop;
        loop.push(Number(true, 1));
        while(!loop.empty()) {
            string cmd;
            cin >> cmd;

            if(cmd == "BEGIN") continue;
            else if(cmd == "END") {
                Number n = loop.top();
                int cur = loop.size()-1;
                loop.pop();

                if(n.integer) {
                    for(int i = 0; i < 11; ++i) {
                        cnt[cur][i] *= n.value;
                    }
                }
                else {
                    for(int i = 10; i > 0; --i) {
                        cnt[cur][i] = cnt[cur][i-1];
                    }
                    cnt[cur][0] = 0;
                }

                if(cur > 0) {
                    for(int i = 0; i < 11; ++i) {
                        cnt[cur-1][i] += cnt[cur][i];
                    }
                    cnt.pop_back();
                }
            }
            else if(cmd == "LOOP") {
                string num;
                cin >> num;
                Number n;
                if(num == "n") n.integer = false;
                else {
                    n.integer = true;
                    n.value = atoi(num.c_str());
                }
                loop.push(n);
                cnt.push_back(vector<int>(11, 0));
            }
            else if(cmd == "OP") {
                int n;
                cin >> n;
                cnt[loop.size()-1][0] += n;
            }
        }

        cout << "Program #" << CASE << endl;
        cout << "Runtime = ";
        bool first = true;
        for(int i = 10; i >= 0; --i) {
            if(cnt[0][i]) {
                if(!first) cout << '+';
                if(i == 0) cout << cnt[0][i];
                else {
                    if(cnt[0][i] > 1) cout << cnt[0][i] << '*';
                    cout << "n";
                    if(i > 1) cout << '^' << i;
                }
                first = false;
            }
        }
        if(first) cout << 0;
        cout << endl;
        cout << endl;
    }

    return 0;
}

