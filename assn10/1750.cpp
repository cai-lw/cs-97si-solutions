#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string st;
    while (!cin.eof()) {
        string s;
        cin >> s >> ws;
        int i = 0;
        while(i < st.length() && i < s.length() && st[i] == s[i]) i++;
        st.resize(i);
        if(i < s.length()) st.push_back(s[i]);
        cout << string(i, ' ') << s << endl;
    }
}