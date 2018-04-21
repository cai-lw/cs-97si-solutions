#include <cstdio>
#include <algorithm>
using namespace std;

bool a[1001][1001];
int e[1001][1001], d[1001], n, m;

void dfs(int u, bool *vis){
    for(int i = 0; i < d[u]; i++) {
        int v = e[u][i];
        if(!vis[v]){
            vis[v] = true;
            dfs(v, vis);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    fill(d, d+n, 0);
    for(int i = 0; i < n; i++){
        fill(a[i], a[i]+n, false);
        a[i][i] = true;
    }
    for(int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        e[x][d[x]]=y;
        d[x]++;
    }
    for(int i = 0; i < n; i++) dfs(i, a[i]);
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(!a[i][j] && !a[j][i])ans++;
    printf("%d\n", ans);
}