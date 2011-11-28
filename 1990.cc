#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int leftsum, myself, rightsum;
    int v, cnt;

    Node() : leftsum(0), myself(0), rightsum(0), v(-1), cnt(0) {}
};
Node distance_sum[20001];

int find(int v) {
    int n = 1;
    while(distance_sum[n].v != -1) {
        if(distance_sum[n].v == v) return n;
        else if(v < distance_sum[n].v) n *= 2;
        else n = n*2+1;
    }
    distance_sum[n].v = v;
    return n;
}

void insert(int v, int x) {
    int n = find(v);
    distance_sum[n].myself += x;
    ++distance_sum[n].cnt;

    while(n>1) {
        if(n&1) distance_sum[n/2].rightsum += x;
        else distance_sum[n/2].leftsum += x;
        n /= 2;
    }
}

int main() {
    int N;
    cin >> N;

    vector<pair<int, int> > cows;
    for(int i = 0; i < N; ++i) {
        int v, x;
        cin >> v >> x;
        cows.push_back(make_pair(x, v));
    }
    sort(cows.begin(), cows.end());

    insert(cows[0].second, cows[0].first);
    for(int i = 1; i < N; ++i) {
        int n = find(cows[i].second);
        distance_sum[n].
