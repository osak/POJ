//Name: Trees Made to Order
//Level: 3
//Category: 数論,二分木,順序付け,再帰
//Note: 

/*
 * まず必要な葉の数を求め、次に左半分の木、右半分の木の順番で決定していく。
 * 構造は再帰的だが、左半分、右半分が具体的にどういう値になるかを計算するのが大変。
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int> pat;

string gentree(int num) {
    if(num == 0) return "";

    //Determine number of leaves
    int lb, ub = 0;
    int leaves = 0;
    while(true) {
        if(ub >= num) break;
        lb = ub+1;
        ++leaves;
        ub += pat[leaves];
    }
    int lb1 = lb;

    //Determine left tree
    int lleaves = 0;
    ub = lb + pat[lleaves]*pat[leaves-1-lleaves]-1;
    while(true) {
        if(ub >= num) break;
        lb = ub+1;
        ++lleaves;
        ub += pat[lleaves]*pat[leaves-1-lleaves];
    }
    int lb2 = lb;

    int rleaves = leaves-1-lleaves;
    int leftidx = (num-lb2) / pat[rleaves];
    int rightidx = (num-lb2) % pat[rleaves];
    int loffset = 0, roffset = 0;
    for(int i = 0; i < lleaves; ++i) loffset += pat[i];
    for(int i = 0; i < rleaves; ++i) roffset += pat[i];
    string left = gentree(leftidx + loffset);
    string right = gentree(rightidx + roffset);
    if(left.size() > 0) left = "(" + left + ")";
    if(right.size() > 0) right = "(" + right + ")";

    return left + "X" + right;
}

int main() {
    pat.push_back(1);
    pat.push_back(1);

    int total = 0;
    for(int n = 2; ; ++n) {
        int cnt = 0;
        for(int i = 0; i < n; ++i) cnt += pat[i]*pat[n-i-1];
        pat.push_back(cnt);
        total += cnt;
        if(total >= 500000000) break;
    }
    
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        cout << gentree(N) << endl;
    }
    return 0;
}
           
