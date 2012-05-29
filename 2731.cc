//Name: ACM(ACronymMaker)
//Level: 3
//Category: 文字列,DP,LCS
//Note: long longにしたら通った

/*
 * 縦軸にabbreviation，横軸に単語を並べたものでLongest Common Subsequenceを求めれば良い．
 * ただし各単語から最低1文字は取らないといけない，という条件があるので，
 * 単語ごとにグループ分けしてグループ間の状態遷移も考えるようにする．
 * 最終的には
 * [abbrの位置][単語のindex][単語の位置]
 * のDPになり，dp[i][j][k] = dp[i-1][j-1][abbr[i-1]と一致するもの] +
 *                           dp[i-1][j][abbr[i-1]と一致するもの]
 * となる．
 * 問題文には32bit signed integerで収まるようなことが書いてあるが，intでやったら通らなかった．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <sstream>
#include <cctype>

using namespace std;

long long solve(const string &abbr, const vector<string> &words) {
    const int ALEN = abbr.size();
    const int WLEN = words.size();

    for(int i = 0; i < WLEN; ++i) {
        if(words[i].size() == 0) return 0;
    }

    // [一致した場所][グループ][位置]
    vector<vector<vector<long long> > > dp(ALEN, vector<vector<long long> >(WLEN));
    for(int i = 0; i < ALEN; ++i) {
        for(int j = 0; j < WLEN; ++j) {
            dp[i][j].resize(words[j].size(), 0);
        }
    }

    // Base Case: 1文字目は必ず1語目
    for(int i = 0; i < (int)words[0].size(); ++i) {
        char need = tolower(abbr[0]);
        if(words[0][i] == need) {
            dp[0][0][i] = 1;
        }
    }
    for(int i = 1; i < ALEN; ++i) {
        const char prev_need = tolower(abbr[i-1]);
        const char need = tolower(abbr[i]);
        for(int j = 0; j < WLEN; ++j) {
            for(int k = 0; k < (int)words[j].size(); ++k) {
                if(words[j][k] == need) {
                    // 前のグループから来るとき
                    if(j > 0) {
                        for(int prev_k = 0; prev_k < (int)words[j-1].size(); ++prev_k) {
                            if(words[j-1][prev_k] == prev_need) {
                                dp[i][j][k] += dp[i-1][j-1][prev_k];
                            }
                        }
                    }
                    // 同じグループから来るとき
                    if(k > 0) {
                        for(int prev_k = 0; prev_k < k; ++prev_k) {
                            if(words[j][prev_k] == prev_need) {
                                dp[i][j][k] += dp[i-1][j][prev_k];
                            }
                        }
                    }
                }
            }
        }
    }

    // 答えは最終グループで最後の文字を取れているものの合計
    long long res = 0;
    for(int i = 0; i < (int)words.back().size(); ++i) {
        res += dp[ALEN-1][WLEN-1][i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        set<string> ng_word;
        while(N--) {
            string str;
            cin >> str;
            ng_word.insert(str);
        }
        {
            string dmy;
            getline(cin, dmy);
        }
        while(true) {
            string line;
            getline(cin, line);
            if(line == "LAST CASE") break;

            string abbr;
            vector<string> words;

            istringstream is(line);
            is >> abbr;
            vector<bool> has_char(26, false);
            for(int i = 0; i < (int)abbr.size(); ++i) {
                has_char[abbr[i]-'A'] = true;
            }
            {
                string word;
                while(is >> word) {
                    if(ng_word.count(word)) continue;
                    string valid_str;
                    for(int i = 0; i < (int)word.size(); ++i) {
                        if(has_char[word[i]-'a']) valid_str += word[i];
                    }
                    //cout << valid_str << endl;
                    words.push_back(valid_str);
                }
            }

            long long cnt = solve(abbr, words);
            if(cnt) {
                cout << abbr << " can be formed in " << cnt << " ways" << endl;
            }
            else {
                cout << abbr << " is not a valid abbreviation" << endl;
            }
        }
    }

    return 0;
}
