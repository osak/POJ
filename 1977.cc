//Name: Odd Loving Bakers
//Level: 3
//Category: 行列
//Note:

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Matrix {
    vector<vector<int> > v;

    int rows() const { return v.size(); }
    int cols() const { return v[0].size(); }

    int get(int r, int c) const {
        return v[r][c];
    }

    int set(int r, int c, int val) {
        v[r][c] = val;
    }

    Matrix& operator *= (const Matrix &other) {
        Matrix m = *this * other;
        v.swap(m.v);
        return *this;
    }

    friend Matrix operator * (const Matrix &m1, const Matrix &m2) {
        Matrix res(m1.rows(), m2.cols());

        for(int i = 0; i < m1.rows(); ++i) {
            for(int j = 0; j < m2.cols(); ++j) {
                int sum = 0;
                for(int k = 0; k < m1.cols(); ++k)
                    sum += m1.get(i, k) * m2.get(k, j);
                res.set(i, j, sum % 2);
            }
        }
        return res;
    }

    Matrix(int r, int c) {
        v.resize(r);
        for(int i = 0; i < r; ++i) {
            v[i].resize(c);
            fill(v[i].begin(), v[i].end(), 0);
        }
    }
};


Matrix matpow(const Matrix &m, int p) {
    if(p == 0) {
        Matrix res(m.rows(), m.cols());
        for(int i = 0; i < m.rows(); ++i)
            res.set(i, i, 1);
        return res;
    }
    if(p == 1) return m;

    int left = p/2;
    int right = (p+1)/2;
    Matrix tmp = matpow(m, left);

    if(left == right) return tmp * tmp;
    else return tmp * tmp * m;
}

int main() {
    int X;
    cin >> X;
    while(X--) {
        int N, T;
        cin >> N >> T;

        map<string, int> m;
        int seq = 0;
        Matrix mat(N, N);
        Matrix vec(N, 1);

        for(int i = 0; i < N; ++i) {
            string name;
            int init, n;
            cin >> name >> init >> n;

            if(m.count(name) == 0) m[name] = seq++;
            int id = m[name];

            if(init & 1) vec.set(id, 0, 1);
            mat.set(id, id, 1);

            for(int j = 0; j < n; ++j) {
                string s;
                cin >> s;
                if(m.count(s) == 0) m[s] = seq++;
                int sid = m[s];
                if(sid == id) mat.set(sid, id, 0);
                else mat.set(sid, id, 1);
            }
        }

        Matrix tmp = matpow(mat, T-1) * vec;
        int cnt = 0;
        for(int i = 0; i < N; ++i)
            if(tmp.get(i, 0)) ++cnt;
        cout << cnt << endl;
    }
    return 0;
}
