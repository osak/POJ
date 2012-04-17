//Name: Corporate Identity
//Level: 3
//Category: 文字列,Suffix Array
//Note: Suffix Array確認問題

/*
 * 最初の文字列の全てのsuffixを生成し，その他の文字列が先頭からそのsuffixを先頭何文字までなら含んでいるかを判定する．
 * この判定はsuffix arrayによる比較に手を加えれば，文字列長Nに対してO(N log N)で可能．
 */
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace std;

struct SAComp {
    const vector<int> *grp;
    int h;
    SAComp(const vector<int> *grp, int h) : grp(grp), h(h) {}

    bool operator ()(int a, int b) const {
        int va = grp->at(a);
        int vb = grp->at(b);
        int vah = a+h < grp->size() ? grp->at(a+h) : INT_MIN;
        int vbh = b+h < grp->size() ? grp->at(b+h) : INT_MIN;
        return (va == vb) ? vah < vbh : va < vb;
    }
};

// Suffix Arrayを構築する．
// A Fast Algorithm for Making Suffix Arrays and for Burrows-Wheeler Transformation
// (Kunihiko Sadakane, 1998)
// の実装．ただし，以下の変更を加えている．
// ・同じグループごとにソートするのではなく，Suffix Array全体を一度にソートする．
//
// 計算量O(N (log N)^2)
void suffix_array(const string &str, vector<int> &sa) {
    assert(sa.size() >= str.size());

    int N = str.size();
    vector<int> group(N, 0), next(N, 0);
    for(int i = 0; i < N; ++i) {
        sa[i] = i;
        group[i] = str[i];
    }
    {
        SAComp cmp(&group, 0);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }

    for(int h = 1; h < N && group[N-1] != N-1; h <<= 1) {
        //Generate <_{2*h} ordered array from <_{h} ordered array
        //この中身はcmpのコンストラクタ引数以外，上のブロックと同じ．
        SAComp cmp(&group, h);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }
}

pair<int,int> compare(int pos, int len, const string &s1, const string &s2) {
    int i;
    for(i = 0; i < len; ++i) {
        if(s1[i+pos] != s2[i]) break;
    }
    if(i == len) return make_pair(0, i);
    return make_pair(s1[i+pos]-s2[i], i);
}

int find(const string &src, const string &str, const vector<int> &sa) {
    int left = 0, right = sa.size();
    int maxlen = 0;
    while(left < right) {
        int mid = (left+right)/2;
        int len = min(src.size()-sa[mid], str.size());
        pair<int,int> res = compare(sa[mid], len, src, str);
        //cout << src.substr(sa[mid]) << ' ' << res.first << ' ' << res.second << endl;
        maxlen = max(maxlen, res.second);
        if(res.first == 0 && len == str.size()) break;
        if(res.first < 0 || (res.first == 0 && len < str.size())) left = mid+1;
        else right = mid;
    }
    return maxlen;
}

int main() {
    ios::sync_with_stdio(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<string> strs(N);
        for(int i = 0; i < N; ++i) {
            cin >> strs[i];
        }

        vector<vector<int> > sarrays(N);
        for(int i = 0; i < N; ++i) {
            sarrays[i] = vector<int>(strs[i].size(), 0);
            suffix_array(strs[i], sarrays[i]);
        }

        string ans;
        int maxlen = 0;
        for(int start = 0; start < strs[0].size(); ++start) {
            const string suffix = strs[0].substr(start);
            int bestlen = suffix.size();
            for(int i = 1; i < N; ++i) {
                bestlen = min(bestlen, find(strs[i], suffix, sarrays[i]));
                //cout << suffix << " " << bestlen << endl;
            }
            if(bestlen >= maxlen) {
                const string sub = suffix.substr(0, bestlen);
                if(bestlen > maxlen || (bestlen == maxlen && sub < ans)) {
                    maxlen = bestlen;
                    ans = sub;
                }
            }
        }

        if(maxlen == 0) {
            cout << "IDENTITY LOST" << endl;
        }
        else {
            cout << ans << endl;
        }
    }

    return 0;
}
