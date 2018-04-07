#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct LEntry {
    int p1, p2, idx;
    bool operator<(LEntry &other) {
        return p1 < other.p1 || (p1 == other.p1 && p2 < other.p2);
    }
};

int p[30][200011], sa[200011], step, n;
LEntry l[200011];
string s;

void suffix_array() {
    for(int i=0;i<n;i++)p[0][i]=int(s[i]);
    for(int cnt=1;cnt*2<n;cnt*=2) {
        step++;
        for(int i=0;i<n;i++){
            l[i].p1 = p[step - 1][i];
            l[i].p2 = i + cnt < n ? p[step - 1][i + cnt] : -1;
            l[i].idx = i;
        }
        sort(l, l + n);
        for (int i=0;i<n;i++) {
            p[step][l[i].idx] = i > 0 && l[i].p1 == l[i - 1].p1 && l[i].p2 == l[i - 1].p2 ? p[step][l[i - 1].idx] : i;
        }
    }
}

int lcp(int x, int y) {
    int ret = 0;
    if (x == y) return n - x;
    for (int k = step; k >= 0 && x < n && y < n; k--) {
        if (p[k][x] == p[k][y]) {
            x += 1 << k;
            y += 1 << k;
            ret += 1 << k;
        }
    }
    return ret;
}

int main() {
    string A, B;
    cin >> A;
    cin >> B;
    s = A + '#' + B;
    n = s.length();
    step = 0;
    suffix_array();
    for(int i=0;i<n;i++)sa[p[step][i]]=i;
    int ans=0, last_A=-1, last_B=-1;
    for(int i=0;i<n-1;i++){
        if (sa[i] == A.length() || sa[i+1] == A.length()) continue;
        if ((sa[i] < A.length()) ^ (sa[i+1] < A.length()))
            ans = max(ans, lcp(sa[i], sa[i+1]));
    }
    cout << ans << endl;
}