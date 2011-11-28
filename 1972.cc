#include <iostream>

using namespace std;

int rev[] = {5, 3, 4, 1, 2, 0};

int dice[10000][6];
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 6; ++j) {
                cin >> dice[i][j];
            }
        }
        int result = 0;
        //Bottom dice
        for(int i = 0; i < 6; ++i) {
            int topnum = dice[0][i];
            int sum = 0;
            //For each dice
            for(int j = 0; j < n; ++j) {
                //find the max
                int bottomface = 0;
                for(int k = 0; k < 6; ++k) {
                    if(dice[j][k] == topnum) {
                        bottomface = k;
                        break;
                    }
                }
                int maxnum = 0;
                for(int k = 0; k < 6; ++k) {
                    if(k == bottomface || k == rev[bottomface]) continue;
                    if(dice[j][k] > maxnum) maxnum = dice[j][k];
                }
                topnum = dice[j][rev[bottomface]];
                sum += maxnum;
            }
            if(sum > result) result = sum;
        }
        cout << result << endl;
    }
    return 0;
}
