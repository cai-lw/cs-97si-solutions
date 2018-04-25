#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

#define N 1001
int edges[N][N], deg[N], comps[N][N], nc[N], prv[N], nxt[N], n, m, ncomp;
bool vis[N];

void dfs(int u) {
    comps[ncomp][nc[ncomp]++] = u;
    vis[u] = true;
    for(int i = 0; i < deg[u]; i++) {
        int v = edges[u][i];
        if(!vis[v]) dfs(v);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    fill(deg, deg + n, 0);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--;
        v--;
        edges[u][deg[u]++] = v;
        edges[v][deg[v]++] = u;
    }
    fill(nc, nc + n, 0);
    fill(vis, vis + n, false);
    ncomp = 0;
    for(int i = 0; i < n; i++)
        if(!vis[i]) {
            dfs(i);
            ncomp++;
        }
    map<int, bool> ep;
    for(int i = 0; i < ncomp; i++) {
        sort(comps[i], comps[i] + nc[i]);
        for(int j = 0; j < nc[i] - 1; j++) {
            prv[comps[i][j+1]] = comps[i][j];
            nxt[comps[i][j]] = comps[i][j+1];
        }
        if(nc[i] > 1) {
            prv[comps[i][0]] = comps[i][nc[i]-1] - n;
            nxt[comps[i][nc[i]-1]] = comps[i][0] + n;
            ep[comps[i][0]] = true;
            ep[comps[i][nc[i] - 1]] = false;
        }
    }
    int ans = n;
    for(int i = 0; i < n; i++) {
        int cnt = 0, len = 0, head;
        for(map<int, bool>::iterator it = ep.begin(); it != ep.end(); it++) {
            if(cnt == 0) head = it->first;
            if(it->second) cnt++; else cnt--;
            if(cnt == 0) len += it->first - head;
        }
        ans = min(ans, len);
        if(ep.erase(i)) {
            ep.erase(prv[i] + n);
            ep[nxt[i]] = true;
            ep[i + n] = false;
        }
    }
    printf("%d\n", ans);
}