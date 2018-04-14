#include <cstdio>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

struct LEntry {
    int p1, p2, idx;
    bool operator<(LEntry &other) {
        return p1 < other.p1 || (p1 == other.p1 && p2 < other.p2);
    }
};

int p[30][20000], sa[20000], cp[20000], s[20000], step, n, k;
LEntry l[20000];

void suffix_array() {
    for(int i=0;i<n;i++)p[0][i]=s[i];
    for(int cnt=1;cnt<n;cnt*=2) {
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
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", &s[i]);
    step = 0;
    suffix_array();
    for(int i = 0; i < n; i++)sa[p[step][i]] = i;
    multiset<int> cps;
    int ans = 0;
    for(int i = 0; i < n - 1; i++){
        cp[i] = lcp(sa[i], sa[i+1]);
        cps.insert(cp[i]);
        if(cps.size() == k-1){
            ans = max(ans, *cps.begin());
            cps.erase(cps.find(cp[i-k+2]));
        }
    }
    printf("%d\n", ans);
}