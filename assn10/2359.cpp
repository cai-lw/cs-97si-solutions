#include <iostream>
#include <string>
using namespace std;

const int K = 1999;
int dp[30001];

int main() {
    string s, line;
    while(!cin.eof()) {
        getline(cin, line);
        s += line;
    }
    int n = s.length();
    dp[0] = 0;
    for(int i = 1; i < n; i++)
        dp[i] = (dp[i-1] + K) % (i+1);
    switch(s[dp[n-1]]){
        case '?': cout << "Yes" << endl;break;
        case ' ': cout << "No" << endl;break;
        default: cout << "No comments" << endl;
    }
}