//Name: Color Me Less
//Level: 1
//Category: やるだけ
//Note: 

/*
 * やるだけ。3次元ベクトルの距離。
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Color {
    int r, g, b;
};

int distance2(const Color &c1, const Color &c2) {
    return pow(c1.r-c2.r, 2) + pow(c1.g-c2.g, 2) + pow(c1.b-c2.b, 2);
}

ostream& operator<< (ostream &os, const Color &c) {
    os << "(" << c.r << "," << c.g << "," << c.b << ")";
    return os;
}

int main() {
    vector<Color> colors(16);
    for(int i = 0; i < 16; ++i) 
        cin >> colors[i].r >> colors[i].g >> colors[i].b;

    while(true) {
        Color c;
        cin >> c.r >> c.g >> c.b;
        if(c.r == -1 && c.g == -1 && c.b == -1) break;

        int mindist = 65536*3;
        int bestidx = 0;
        for(int i = 0; i < 16; ++i) {
            int d = distance2(c, colors[i]);
            if(d < mindist) {
                mindist = d;
                bestidx = i;
            }
        }

        cout << c << " maps to " << colors[bestidx] << endl;
    }
    return 0;
}
