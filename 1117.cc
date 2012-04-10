//Name: Pairs of Integers
//Level: 3
//Category: 探索
//Note:

/*
 * 下の桁から決めていき，その桁が求める数字になるかどうかで枝刈りする．
 * 途中で1桁飛ばしたところからは桁がずれていくことに注意．
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef pair<string,int> AnsTag;

bool cmp(const AnsTag &a, const AnsTag &b) {
    int aval = atoi(a.first.c_str());
    int bval = atoi(b.first.c_str());
    return aval < bval;
}

bool eql(const AnsTag &a, const AnsTag &b) {
    return a.first == b.first;
}

const int ORD[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
};

vector<AnsTag> ans;

int N;
bool rec(int n, int skipped, int acc, const string &number) {
    int ord = ORD[n];
    if(acc > N) return false;
    if(acc == N && skipped != -1) {
        if(number[0] != '0') ans.push_back(AnsTag(number, skipped));
        return true;
    }
    if(ord > N) return false;
    if(n > 9) return false;

    for(int d = 0; d <= 9; ++d) {
        char buf[2];
        buf[0] = '0'+d;
        buf[1] = 0;
        const string next = string(buf)+number;
        if(skipped != -1) {
            int na = acc + d*ord + d*ORD[n-1];
            if(na / ORD[n-1] % 10 == N / ORD[n-1] % 10) {
                rec(n+1, skipped, na, next);
            }
        }
        else {
            // not skip
            int na = acc + d*2*ord;
            if(na / ord % 10 == N / ord % 10) {
                rec(n+1, skipped, na, next);
            }

            // skip
            na = acc + d*ord;
            rec(n+1, n, na, next);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N;
    rec(0, -1, 0, "");

    sort(ans.begin(), ans.end(), cmp);
    ans.erase(unique(ans.begin(), ans.end(), eql), ans.end());
    cout << ans.size() << endl;
    for(vector<AnsTag>::iterator it = ans.begin(); it != ans.end(); ++it) {
        string rhs = it->first;
        rhs.erase(rhs.begin() + ((int)rhs.size()-it->second-1));
        cout << it->first << " + " << rhs << " = " << N << endl;
    }

    return 0;
}
