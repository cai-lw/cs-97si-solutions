#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1000000000;
int n, a[15][15], deg[15], ans, sm;
bool odd[15];

void search() {
    if(sm >= ans) return;
    int base = -1;
    for(int i = 0; i < n; i++) {
        if(odd[i])
            if(base == -1) {
                odd[i] = false;
                base = i;
            }
            else {
                odd[i] = false;
                sm += a[base][i];
                search();
                sm -= a[base][i];
                odd[i] = true;
            }
    }
    if(base >= 0) odd[base] = true;
    else ans = sm;
}

int main() {
    while(true) {
        scanf("%d", &n);
        if(n == 0) break;
        fill(deg, deg + n, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)a[i][j] = INF;
            a[i][i] = 0;
        }
        int m, tot = 0;
        scanf("%d", &m);
        for(int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d %d %d", &u, &v, &d);
            u--;
            v--;
            a[u][v] = min(a[u][v], d);
            a[v][u] = min(a[v][u], d);
            tot += d;
            deg[u]++;
            deg[v]++;
        }
        for(int i = 0; i < n; i++)odd[i] = deg[i] % 2;
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        ans = INF;
        sm = 0;
        search();
        printf("%d\n", ans + tot);
    }
}