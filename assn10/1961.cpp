#include <iostream>
#include <string>
using namespace std;

int nxt[1000000];

int main() {
    string s;
    int n, cas = 0;
    cin >> n;
    while(n > 0) {
        cout << "Test case #" << ++cas << endl;
        cin >> s;
        nxt[0] = -1;
        for (int i = 1; i < n; i++) {
            int j = nxt[i - 1];
            while (s[j + 1] != s[i] && j >= 0) j = nxt[j];
            if (s[j + 1] == s[i]) nxt[i] = j + 1;
            else nxt[i] = -1;
            if (nxt[i] >= 0 && (i + 1) % (i - nxt[i]) == 0)
                cout << i + 1 << ' ' << (i + 1) / (i - nxt[i]) << endl;
        }
        cin >> n;
        if (n > 0) cout << endl;
    }
}