#include <iostream>
#include <string>
using namespace std;

int main() {
    string pat, s;
    while(!cin.eof()) {
        cin >> pat >> s >> ws;
        int j = 0;
        for(int i = 0; i < s.length(); i++) {
            if(j < pat.length() && s[i] == pat[j]) j++;
        }
        if (j == pat.length()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}