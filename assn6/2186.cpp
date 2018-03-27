#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<int> graph[10000];
stack<int> st;
int n, m, dfs_count, comp_count, dfn[10000], low[10000], comp[10000], dout[10000];
bool in_stack[10000];

void scc(int u) {
    dfn[u] = ++dfs_count;
    low[u] = dfn[u];
    st.push(u);
    in_stack[u] = true;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if (dfn[v] == 0) {
            scc(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v;
        comp_count++;
        do {
            v = st.top();
            st.pop();
            in_stack[v] = false;
            comp[v] = comp_count;
        } while (u != v);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) graph[i] = vector<int>();
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
    }
    st = stack<int>();
    dfs_count = 0;
    comp_count = 0;
    fill(dfn, dfn + n, 0);
    fill(in_stack, in_stack + n, false);
    for (int u = 0; u < n; u++)
        if (dfn[u] == 0) scc(u);
    fill(dout, dout + comp_count, 0);
    for (int u = 0; u < n; u++)
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if (comp[u] != comp[v]) dout[comp[u] - 1]++;
        }
    int end_comp, end_count = 0;
    for (int i = 0; i < comp_count; i++)
        if (dout[i] == 0) {
            end_count++;
            end_comp = i + 1;
        }
    if (end_count == 1) {
        int ans = 0;
        for (int u = 0; u < n; u++)
            if (comp[u] == end_comp) ans++;
        printf("%d\n", ans);
    }
    else printf("0\n");
}