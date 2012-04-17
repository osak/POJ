//Name: Document Indexing
//Level: 3
//Category: 強実装
//Note:

/*
 * 問題文の通りに実装するだけ．
 * 実装は辛いが，幸いにも構成要素が最初から分離しているので
 * それぞれのケースに対応するテストを書いて乗り切る．
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int paragraph_line_cnt(int pos, const vector<string> &lines) {
    const int N = lines.size();
    int i;
    for(i = 0; i+pos < N; ++i) {
        if(lines[i+pos] == "") break;
    }
    return i;
}

int whole_paragraph_line_cnt(int pos, const vector<string> &lines) {
    while(pos > 0 && lines[pos] != "") --pos;
    return paragraph_line_cnt(pos+1, lines);
}

int main() {
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    cin.ignore();

    vector<string> lines;
    { 
        string line;
        while(getline(cin, line)) {
            lines.push_back(line);
        }
    }

    vector<int> pages(lines.size());
    int page = 1;
    int pos = 0;
    int acc = 0;
    while(pos < lines.size()) {
        //cout << pos <<  ' ' << acc << endl;
        int cnt = paragraph_line_cnt(pos, lines);
        if(lines[pos] == "") {
            pages[pos] = -1;
            ++pos;
            if(++acc == N) {
                ++page;
                acc = 0;
            }
        }
        else if(acc+cnt == N+1) {
            // If the last line on a page is the next-to-last line of the paragraph
            int wcnt = whole_paragraph_line_cnt(pos, lines);
            if(wcnt > 3) {
                // that contains more than three lines, this line is moved to the next page.
                cnt -= 2;
                for(int i = 0; i < cnt; ++i) {
                    pages[pos+i] = page;
                }
                pos += cnt;
                ++page;
                acc = 0;
            }
            else {
                // that contains exactly two or three lines, whole paragraph moved to the next page.
                ++page;
                while(pos > 0 && lines[pos] != "") --pos;
                ++pos;
                for(int i = 0; i < wcnt; ++i) {
                    pages[pos+i] = page;
                }
                pos += wcnt;
                acc = wcnt;
            }
        }
        else if(cnt > 1 && acc == N-1) {
            // If the last line on a page is the first line of the paragraph of length > 1
            // it is moved to the next page.
            ++page;
            acc = 0;
        }
        else if(acc+cnt == N) {
            // If the last line on a page is the last line of the paragraph
            // following empty line is skipped.
            for(int i = 0; i < cnt; ++i) {
                pages[pos+i] = page;
            }
            pos += cnt;
            ++pos; // skip empty
            ++page;
            acc = 0;
        }
        else {
            int i;
            for(i = 0; i < cnt; ++i) {
                pages[pos+i] = page;
                if(++acc == N) break;
            }
            if(i < cnt) ++i;
            //cout << pos << ' ' << i << endl;
            pos += i;
            if(acc == N) {
                ++page;
                acc = 0;
            }
        }
    }
    /*
    for(int i = 0; i < lines.size(); ++i) {
        cout << pages[i] << ": " << lines[i] << endl;
    }
    */

    map<string,set<int> > m;
    for(int i = 0; i < lines.size(); ++i) {
        for(string::iterator it = lines[i].begin(); it != lines[i].end(); ++it) {
            if(isalpha(*it)) *it = toupper(*it);
            else *it = ' ';
        }
        istringstream is(lines[i]);
        string token;
        while(is >> token) {
            m[token].insert(pages[i]);
        }
    }

    for(map<string,set<int> >::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << ' ';
        bool first = true;
        int prev = -1;
        int start = -1;
        for(set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if(prev == -1) {
                start = *it2;
            }
            else {
                if(*it2 != prev+1) {
                    if(!first) cout << ",";
                    if(start == prev) cout << start;
                    else if(start+1 == prev) cout << start << ',' << prev;
                    else cout << start << '-' << prev;
                    first = false;
                    start = *it2;
                }
            }
            prev = *it2;
        }
        if(!first) cout << ",";
        if(start == prev) cout << start;
        else if(start+1 == prev) cout << start << ',' << prev;
        else cout << start << '-' << prev;
        cout << endl;
    }
    return 0;
}
