//Name: Problem Bee
//Level: 2
//Category: ハニカム,honeycomb,数学,幾何
//Note:

/*
 * 1辺の長さをaとして，座標p(x,y)を含むHexの中心座標を考える．
 * まず六角形の性質から，Hexの中心はx方向には1.5a，y方向にはa*sqrt(3)/2ごとに分布していることがすぐわかる．
 * これを利用して，単純にpの座標をこれらの値で割って仮の行と列を求める．
 * ただしこのままだと範囲が六角形のため，行や列がずれている可能性がある．
 * よって，近傍6マスを調査し，本当にpが含まれるHexを割り出してやる必要がある．
 * ハニカム構造はボロノイ分割になっているので，この調査ではHexの中心とpの距離を求め，一番近いものが
 * 真のHexである．
 *
 * あとはハニカム上の移動の特性に着目すると，
 * ・最低でも始点のHexと終点のHexの列(X)方向の差だけは移動が必要
 * ・1回の列移動につき，行移動も一緒にできる
 * ことから，移動回数の最小値が求められる．
 * 始点と終点が同じときは中心に行ってはいけないことに注意．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const int DELTA[][2] = { // {DR,DC}
    {0, 0},
    {2, 0},
    {-2, 0},
    {1, 1},
    {-1, 1},
    {1, -1},
    {-1, -1},
};

pair<int,int> get_hex(double x, double y, double side) {
    const double x_unit = side * 1.5;
    const double y_unit = side * sqrt(3) / 2;
    int r_center = (int)(y / y_unit); // row = r_center or neighbor
    int c_center = (int)(x / x_unit); // col = c_center or neighbor
    if(c_center % 2 == 0) {
        if(r_center % 2 == 1) ++r_center;
    }
    else if(c_center % 2 == 1) {
        if(r_center % 2 == 0) ++r_center;
    }

    // このマスと6近傍で一番近いのが求めるマス
    pair<int,int> ans;
    double dist = 1e50;
    for(int i = 0; i < 7; ++i) {
        int row = r_center + DELTA[i][0];
        int col = c_center + DELTA[i][1];
        double d = sqrt(pow(y_unit*row - y, 2) + pow(x_unit*col - x, 2));
        if(d < dist) {
            ans = make_pair(row, col);
            dist = d;
        }
    }

    return ans;
}

ostream& operator <<(ostream &o, const pair<int,int> &p) {
    return o << '(' << p.first << ' ' << p.second << ')';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        double side;
        double xa, ya, xb, yb;
        cin >> side >> xa >> ya >> xb >> yb;
        if(side == 0 && xa == 0 && ya == 0 && xb == 0 && yb == 0) break;
        const double x_unit = side * 1.5;
        const double y_unit = side * sqrt(3) / 2;

        pair<int,int> start_hex = get_hex(xa, ya, side);
        pair<int,int> goal_hex = get_hex(xb, yb, side);
        //cout << start_hex << ' ' << goal_hex << endl;

        int rowd = abs(goal_hex.first - start_hex.first);
        int cold = abs(goal_hex.second - start_hex.second);

        double dist = 2*y_unit * cold;
        if(rowd > cold) dist += 2*y_unit * (rowd-cold);

        if(start_hex == goal_hex) {
            dist += sqrt(pow(ya-yb, 2) + pow(xa-xb, 2));
        }
        else {
            dist += sqrt(pow(y_unit*start_hex.first - ya, 2) + pow(x_unit*start_hex.second - xa, 2));
            dist += sqrt(pow(y_unit*goal_hex.first - yb, 2) + pow(x_unit*goal_hex.second - xb, 2));
        }

        cout.precision(3);
        cout.setf(ios::fixed);
        cout << dist << endl;
    }

    return 0;
}
