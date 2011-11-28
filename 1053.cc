//Name: Set Me
//Level: 2
//Category: 組み合わせ,Special Judge
//Note:

/*
 * nCmで全ての組み合わせを列挙するには、n個中m個が0であとは1の配列を
 * next_permutationで回せば良い。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    while(!cin.eof()) {
        cout << "CARDS:  ";
        vector<string> cards;
        while(true) {
            string card;
            getline(cin, card);
            if(card == "") break;
            cards.push_back(card);
            cout << card << " ";
        }
        cout << endl;
        vector<int> pat(cards.size(), 1);
        pat[0] = pat[1] = pat[2] = 0;

        int setnum = 1;
        do {
            int idx[3];
            int pos = 0;
            for(int i = 0; i < pat.size(); ++i) 
                if(pat[i] == 0) idx[pos++] = i;

            const string &s1 = cards[idx[0]];
            const string &s2 = cards[idx[1]];
            const string &s3 = cards[idx[2]];

            bool ok = true;
            for(int i = 0; i < 4; ++i) {
                if((s1[i] == s2[i] && s2[i] == s3[i]) || (s1[i] != s2[i] && s2[i] != s3[i] && s3[i] != s1[i])) {}
                else {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                if(setnum == 1) cout << "SETS:   ";
                else cout << "        ";
                cout << setnum << ".";
                if(setnum < 100) cout << " ";
                if(setnum < 10) cout << " ";
                cout << s1 << " " << s2 << " " << s3 << endl;
                ++setnum;
            }
        } while(next_permutation(pat.begin(), pat.end()));
        if(setnum == 1) {
            cout << "SETS:   *** None Found ***" << endl;
        }
        cout << endl;
    }

    return 0;
}
