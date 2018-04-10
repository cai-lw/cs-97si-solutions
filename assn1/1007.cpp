#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Term {
    string str;
    int rev;
    bool operator<(const Term &other) const {
        return rev < other.rev;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Term a[100];
    for(int i = 0; i < m; i++) {
        cin >> a[i].str;
        a[i].rev = 0;
        int cnt[4] = {0};
        for(int j = 0; j < n; j++)
            switch(a[i].str[j]) {
                case 'A': cnt[0]++; a[i].rev += cnt[1] + cnt[2] + cnt[3]; break;
                case 'C': cnt[1]++; a[i].rev += cnt[2] + cnt[3]; break;
                case 'G': cnt[2]++; a[i].rev += cnt[3]; break;
                case 'T': cnt[3]++;  break;
            }
    }
    stable_sort(a, a + m);
    for(int i = 0; i < m; i++) cout << a[i].str << endl;
}