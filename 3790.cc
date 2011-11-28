#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> arr(1001, 0);
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 2;
    for(int i = 3; i <= 1000; ++i) {
        for(int j = 0; j <= i/2; ++j) {
            arr[i] += arr[j];
        }
    }

    int N;
    cin >> N;
    for(int C = 1; C <= N; ++C) {
        int n;
        cin >> n;
        cout << C << ' ' << arr[n] << endl;
    }
    return 0;
}

