#include <cstdio>
#include <algorithm>
using namespace std;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int v, int w): v(v), w(w) {}
};

Edge graph[40000][4];
int deg[40000], len[40000], len2[40000], par[40000];

void dfs(int u) {
    len[u] = 0;
    len2[u] = 0;
    for (int i = 0; i < deg[u]; i++) {
        Edge &e = graph[u][i];
        if (par[u] == e.v) continue;
        par[e.v] = u;
        dfs(e.v);
        int vlen = len[e.v] + e.w;
        if (vlen > len[u]) {
            len2[u] = len[u];
            len[u] = vlen;
        }
        else if (vlen > len2[u]) len2[u] = vlen;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    fill(deg, deg + n, 0);
    for (int i = 0; i < m; i++) {
        int u, v, l, dx = 0, dy = 0;
        char d;
        scanf("%d %d %d %c", &u, &v, &l, &d);
        graph[u-1][deg[u-1]++] = Edge(v - 1, l);
        graph[v-1][deg[v-1]++] = Edge(u - 1, l);
    }
    par[0] = -1;
    dfs(0);
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, len[i] + len2[i]);
    printf("%d\n", ans);
}