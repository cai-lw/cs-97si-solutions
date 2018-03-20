#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n, t, p, c, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> par(n + 1, 0);
        vector<bool> vis(n + 1, false);
        for (int i = 0; i < n - 1; i++) {
            scanf("%d %d", &p, &c);
            par[c] = p;
        }
        scanf("%d %d", &a, &b);
        int curr = a;
        while (curr > 0) {
            vis[curr] = true;
            curr = par[curr];
        }
        curr = b;
        while (!vis[curr]) curr = par[curr];
        printf("%d\n", curr);
    }
}