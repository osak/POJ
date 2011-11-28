#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

double func(const vector<double> &v, int p) {
    double ans = 0;
    for(int i = 0; i < v.size(); ++i) {
        ans += pow(v[i], p);
    }
    return ans;
}

vector<double> create_initial(double lb, double ub, double sum, int n) {
    vector<double> res(n, 0);
    /*
    for(int i = 0; i < n; ++i) {
        if(sum > 0) {
            res[i] = ub;
            sum -= ub;
        }
        else {
            res[i] = lb;
            sum -= lb;
        }
    }
    */
    int i;
    for(i = 0; i < n; ++i) {
        if(sum > 0) {
            res[i] = min(ub, sum);
            sum -= ub;
            break;
        }
    }
    for(i++; i+1 < n; i += 2) {
        res[i] = lb;
        res[i+1] = -lb;
    }
    return res;
}

//work for v.size() >= 2
vector<double> create_neighbor(const vector<double> &v, double lb, double ub) {
    vector<double> res = v;
    int i = rand() % res.size();
    int j = rand() % res.size();
    if(j == i) j = (j+1) % res.size();

    double diff_ub = min(ub-res[i], res[j]-lb);
    double diff_lb = max(lb-res[i], res[j]-ub);
    //double diff = diff_lb + ((double)rand()/RAND_MAX) * (diff_ub-diff_lb);
    double diff = diff_ub;
    res[i] += diff;
    res[j] -= diff;
    return res;
}
    
int main() {
    srand(time(NULL));
    int M, P, A, B;
    while(cin >> M >> P >> A >> B) {
        double lb = -1/sqrt(A);
        double ub = sqrt(A);
        double sum = B * sqrt(A);

        if(M == 1) {
            cout << round(pow(ub, P)) << endl;
        }
        else {
            vector<double> v = create_initial(lb, ub, sum, M);
            double best = func(v, P);
            double cur_cost = best;
            double temp = 1000000.0;
            for(int phase = 0; phase < 20000; ++phase) {
                vector<double> neighbor = create_neighbor(v, lb, ub);
                temp *= 0.98;
                double ncost = func(neighbor, P);
                if(ncost > cur_cost) {
                    v = neighbor;
                    cur_cost = ncost;
                    if(ncost > best) {
                        best = ncost;
                    }
                }
                else if(exp((cur_cost-ncost) / temp) > (double)rand() / RAND_MAX) {
                    v = neighbor;
                    cur_cost = ncost;
                }
            }

            cout << round(best) << endl;
        }
    }

    return 0;
}
