#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> graph[5000];
int dfn[5000], low[5000], par[5000], comp[5000], comp_deg[5000];
int dfs_count, comp_count;

void dfs(int u) {
    dfn[u] = ++dfs_count;
    low[u] = dfn[u];
    bool found_par_edge = false;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if (v != par[u] || found_par_edge) {
            if (dfn[v] > 0) low[u] = min(low[u], dfn[v]);
            else {
                par[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
        }
        else found_par_edge = true;
    }
}

void flood(int u) {
    comp[u] = comp_count;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if (comp[v] > 0 && comp[v] != comp[u]) {
            comp_deg[comp[u]-1]++;
            comp_deg[comp[v]-1]++;
            continue;
        }
        if ((dfn[u] < low[v] && par[v] == u) || (dfn[v] < low[u] && par[u] == v)) continue;
        if (comp[v] == 0) flood(v);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) graph[i] = vector<int>();
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }
    dfs_count = 0;
    fill(dfn, dfn + n, 0);
    dfs(0);
    fill(comp, comp + n, 0);
    for (int i = 0; i < n; i++)
        if (comp[i] == 0) {
            comp_count++;
            comp_deg[comp_count-1] = 0;
            flood(i);
        }
    int leaf = 0;
    for (int i = 0; i < comp_count; i++)
        if (comp_deg[i] == 1) leaf++;
    printf("%d\n", (leaf + 1) / 2);
}