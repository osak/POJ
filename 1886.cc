//Name: Borrowers
//Level: 2
//Category: 実装,やるだけ
//Note:

/*
 * 問題文の通りにやるだけ．
 * 書架の配列は最後に番兵を置いておくと楽．
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Book {
    string title, author;

    Book() {}
    Book(const string &t, const string &a) : title(t), author(a) {}
};

bool cmp(const Book *a, const Book *b) {
    if(a->author != b->author) return a->author < b->author;
    return a->title < b->title;
}

Book books[1000];

int main() {
    ios::sync_with_stdio(0);

    map<string,Book*> dict;
    int N;
    for(N = 0; ; ++N) {
        string line;
        getline(cin, line);
        if(line == "END") break;

        int quote = line.find('"', 1);
        string title = line.substr(1, quote-1);
        string author = line.substr(quote+5);
        books[N] = Book(title, author);
        dict[title] = &books[N];
    }
    {
        books[N] = Book("\x7f", "\x7f");
        dict[books[N].title] = &books[N];
        ++N;
    }

    vector<Book*> buffer, shelf(N);
    for(int i = 0; i < N; ++i) {
        shelf[i] = &books[i];
    }
    sort(shelf.begin(), shelf.end(), cmp);

    while(true) {
        string line;
        getline(cin, line);
        if(line[0] == 'B') { // BORROW
            string title = line.substr(8, line.size()-8-1);
            Book *b = dict[title];
            vector<Book*>::iterator it = find(shelf.begin(), shelf.end(), b);
            shelf.erase(it);
        }
        else if(line[0] == 'R') { // RETURN
            string title = line.substr(8, line.size()-8-1);
            Book *b = dict[title];
            buffer.push_back(b);
        }
        else if(line[0] == 'S') { // SHELVE
            sort(buffer.begin(), buffer.end(), cmp);
            vector<Book*>::iterator shelf_it = shelf.begin();
            for(vector<Book*>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
                for(; ; ++shelf_it) {
                    if(cmp(*it, *shelf_it)) {
                        if(shelf_it == shelf.begin()) {
                            cout << "Put \"" << (*it)->title << "\" first" << endl;
                        }
                        else {
                            vector<Book*>::iterator prev = shelf_it-1;
                            cout << "Put \"" << (*it)->title << "\" after \"" << (*prev)->title << "\"" << endl;
                        }
                        shelf_it = shelf.insert(shelf_it, *it);
                        break;
                    }
                }
            }
            cout << "END" << endl;
            buffer.clear();
        }
        else if(line[0] == 'E') { // END
            break;
        }
    }

    return 0;
}
