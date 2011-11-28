#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    string str;
    cin >> str;
    
    string result;
    if(str.find_first_of("_") != -1) {
        bool next_is_upper = false;
        for(int i = 0; i < str.length(); ++i) {
            if(str[i] == '_') {
                next_is_upper = true;
            }
            else {
                if(next_is_upper) {
                    if(isupper(str[i]) || str[i]=='_') {
                        result = "Error!";
                        break;
                    }
                    result += toupper(str[i]);
                    next_is_upper = false;
                }
                else {
                    result += str[i];
                }
            }
        }
    }
    else {
        for(int i = 0; i < str.length(); ++i) {
            if(islower(str[i])) {
                result += str[i];
            }
            else if(!isalpha(str[i])) {
                result = "Error!";
                break;
            }
            else {
                result += '_';
                result += tolower(str[i]);
            }
        }
    }
    cout << result << endl;

    return 0;

}
