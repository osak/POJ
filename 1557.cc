//Name: Mapmaker
//Level: 2
//Category: シミュレーション,実装
//Note:

/*
 * C言語の多次元配列のインデックスからアドレスを求めるような問題．
 * それぞれの次元について，1増えたときにアドレスがいくつ増えるかをあらかじめ計算しておくと楽．
 */
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

using namespace std;

struct Array {
    int base, esize;
    vector<pair<int, int> > dims;
    vector<int> step;

    void calc_step() {
        step.resize(dims.size());
        step[dims.size()-1] = esize;
        for(int i = (int)dims.size()-2; i >= 0; --i) {
            step[i] = step[i+1]*(dims[i+1].second-dims[i+1].first+1);
        }
    }
};

int main() {
    int N, R;
    cin >> N >> R;

    map<string, Array> m;
    for(int i = 0; i < N; ++i) {
        string name;
        Array arr;
        int dim;
        cin >> name >> arr.base >> arr.esize >> dim;
        for(int j = 0; j < dim; ++j) {
            pair<int, int> d;
            cin >> d.first >> d.second;
            arr.dims.push_back(d);
        }
        arr.calc_step();
        m[name] = arr;
    }
    while(R--) {
        string name;
        cin >> name;

        const Array &arr = m[name];
        vector<int> indexes(arr.dims.size());
        for(int i = 0; i < indexes.size(); ++i) cin >> indexes[i];
        int addr = arr.base;
        for(int i = 0; i < indexes.size(); ++i) {
            addr += arr.step[i] * (indexes[i]-arr.dims[i].first);
        }
        cout << name << "[";
        for(int i = 0; i < indexes.size(); ++i)
            cout << (i>0?", ":"") << indexes[i];
        cout << "] = ";
        cout << addr << endl;
    }
    return 0;
}
