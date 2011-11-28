#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    while(true) {
        string str;
        cin >> str;
        if(str == "END") break;
        
        map<char,int> m;
        for(int i = 0; i < str.size(); ++i)
            m[str[i]]++;

        vector<int> v;
        for(map<char,int>::iterator it = m.begin(); it != m.end(); ++it)
            v.push_back(it->second);

        sort(v.begin(), v.end(), greater<int>());
        int len = 1;
        int sum = 0;
        for(int i = 0; i < v.size(); ++i) {
            sum += len * v[i];
            if(i < (int)v.size()-2) ++len;
        }
        printf("%d %d %.1f\n", str.size()*8, sum, (double)str.size()*8/sum);
    }
    return 0;
}
