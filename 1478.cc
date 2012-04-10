//Name: Island of Logic
//Level: 2
//Category: 全探索
//Note:

/*
 * 登場人物が5人しかいないので，それぞれの属性と昼夜で全探索する．
 * 特定の属性でないと矛盾が生じるとき，その属性はDeducibleとなる．
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Type { TYPE_DIVINE, TYPE_HUMAN, TYPE_EVIL, TYPE_LYING };
enum Day { DAY_DAY, DAY_NIGHT };

struct Conversation {
    int from, target;
    Type type;
    bool inv;

    Day day;

    Conversation() : inv(false) {}
    Conversation(int f, int t, Type ty, bool i) : from(f), target(t), type(ty), inv(i) {}
};

bool lier(int type, int day) {
    return (type == TYPE_EVIL || (type == TYPE_HUMAN && day == DAY_NIGHT));
}

int main() {
    ios::sync_with_stdio(0);
    for(int CASE = 1; ; ++CASE) {
        int N;
        cin >> N;
        if(!N) break;
        cin.ignore();

        vector<Conversation> convs(N);
        for(int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);

            convs[i].from = line[0]-'A';
            if(line.find("It is") != string::npos) {
                convs[i].target = -1;
                if(line[9] == 'd') {
                    convs[i].day = DAY_DAY;
                }
                else if(line[9] == 'n') {
                    convs[i].day = DAY_NIGHT;
                }
            }
            else {
                convs[i].target = line[3]-'A';
                if(convs[i].target >= 5) { // I am
                    convs[i].target = convs[i].from;
                }
                if(line.find("divine") != string::npos) {
                    convs[i].type = TYPE_DIVINE;
                }
                else if(line.find("human") != string::npos) {
                    convs[i].type = TYPE_HUMAN;
                }
                else if(line.find("evil") != string::npos) {
                    convs[i].type = TYPE_EVIL;
                }
                else if(line.find("lying") != string::npos) {
                    convs[i].type = TYPE_LYING;
                }
                if(line.find("not") != string::npos) {
                    convs[i].inv = true;
                }
            }
        }

        int valid_cnt = 0;
        vector<vector<int> > deduce_cnt(6, vector<int>(3, 0));
        for(int pat = 0; pat < 486; ++pat) {
            vector<int> facts(6);
            for(int i = 0, tmp = pat; i < 6; ++i, tmp /= 3) {
                facts[i] = tmp % 3;
            }

            bool contradict = false;
            for(vector<Conversation>::iterator it = convs.begin(); it != convs.end(); ++it) {
                bool flag;
                if(it->target == -1) {
                    flag = (facts[5] == it->day);
                }
                else {
                    if(it->type == TYPE_LYING) {
                        flag = lier(facts[it->target], facts[5]);
                    }
                    else {
                        flag = (facts[it->target] == it->type);
                    }
                    if(it->inv) flag = !flag;
                }
                if(lier(facts[it->from], facts[5])) flag = !flag;
                if(!flag) {
                    contradict = true;
                    break;
                }
            }
            if(!contradict) {
                ++valid_cnt;
                for(int i = 0; i < 6; ++i) {
                    deduce_cnt[i][facts[i]]++;
                }
            }
        }

        /*
        for(int i = 0; i < 6; ++i) {
            for(int j = 0; j < 3; ++j) {
                cout << deduce_cnt[i][j] << ' ';
            }
            cout << endl;
        }
        */

        cout << "Conversation #" << CASE << endl;
        if(valid_cnt == 0) {
            cout << "This is impossible." << endl;
        }
        else {
            bool deduced = false;

            for(int i = 0; i < 5; ++i) {
                int fact = -1;
                for(int j = 0; j < 3; ++j) {
                    if(deduce_cnt[i][j] == valid_cnt) {
                        if(fact != -1) {
                            fact = -1;
                            break;
                        }
                        fact = j;
                    }
                }
                if(fact != -1) {
                    const string name[] = {"divine", "human", "evil"};
                    cout << char(i+'A') << " is " << name[fact] << "." << endl;
                    deduced = true;
                }
            }
            {
                int fact = -1;
                for(int j = 0; j < 2; ++j) {
                    if(deduce_cnt[5][j] == valid_cnt) {
                        if(fact != -1) {
                            fact = -1;
                            break;
                        }
                        fact = j;
                    }
                }
                if(fact != -1) {
                    const string name[] = {"day", "night"};
                    cout << "It is " << name[fact] << "." << endl;
                    deduced = true;
                }
            }
            if(!deduced) {
                cout << "No facts are deducible." << endl;
            }
        }
        cout << endl;
    }

    return 0;
}
