#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> edges[20001];
int balance[20001];
bool vis[20001];
int n;

int dfs(int u) {
    vis[u] = true;
    int max_size = 0, sub_size = 1;
    for (int i = 0; i < edges[u].size(); i++) {
        int v = edges[u][i];
        if (!vis[v]) {
            int v_size = dfs(v);
            sub_size += v_size;
            max_size = max(max_size, v_size);
        }
    }
    balance[u] = max(max_size, n - sub_size);
    return sub_size;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            vis[i] = false;
            edges[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        dfs(1);
        int ans = n, min_i;
        for (int i = 1; i <= n; i++)
            if (balance[i] < ans) {
                ans = balance[i];
                min_i = i;
            }
        printf("%d %d\n", min_i, ans);
    }
}