#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    while(true) {
        int H, A;
        cin >> H >> A;
        if(!H && !A) break;

        vector<pair<int, int> > human(H);
        vector<pair<int, int> > alien(A);
        vector<vector<int> > cost(H, vector<int>(A));

        for(int 
