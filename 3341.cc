#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define FOREACH(V, E) for(__typeof(E.begin()) V = E.begin(); V != E.end(); ++V)

using namespace std;

struct Road {
    string name;
    int length;
    int minutes;
};

int main() {
    while(true) {
        vector<Road> roads;
        while(true) {
            Road r;
            cin >> r.name >> r.length >> r.minutes;
            if(r.name == "$") break;
            roads.push_back(r);
        }
        string src, dst, t;
        cin >> src >> dst >> t;
        int hour = atoi(t.substr(0, 2).c_str());
        int minute = atoi(t.substr(3).c_str());

        int totallen = 0;
        int totalmin = 0;
        int fare = 0;
        bool go = false;
        FOREACH(road, roads) {
            if(road->name == src) go = true;
            if(go) {
                int end = start+road->minutes;
                if(start <= 6*60) {
                    //double nl = road->length/road->minutes * (min(end, 6*60)-start)
                    int nl = floor(road->length*(min(end, 6*60)-start) / road->minutes);
                    fare += nl * 

                totallen += road->length;
                totalmin += road->minutes;
            }
            if(road->name == dst) break;
        }

        int fare = 0;
        
