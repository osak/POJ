#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}

int main() {
    unsigned C = 1;
    while(true) {
        unsigned int n, m;
        scanf("%u %u", &n, &m);
        if(!n && !m) break;

        vector<int> student(n);
        vector<int> levels(n, 0);
        for(int i = 0; i < n; ++i) {
            student[i] = i;
        }
        int cnt = n;
        while(m--) {
            int i, j;
            scanf("%d %d", &i, &j);
            --i; --j;
            if(unite(i, j, student, levels)) --cnt;
        }

        printf("Case %u: %d\n", C, cnt);
        ++C;
    }
    return 0;
}
