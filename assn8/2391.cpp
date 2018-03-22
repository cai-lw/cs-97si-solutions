#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1000000000000000000;

struct Bfs {
    int u, h;
    Bfs(int u, int h): u(u), h(h) {}
};

class Network {
    int cap[403][403], flow[403][403], height[403], ptr[403];
    bool vis[403];
    int n;
    bool bfs() {
        queue<Bfs> q;
        memset(vis, 0, sizeof(vis));
        q.push(Bfs(0, 0));
        vis[0] = true;
        while(!q.empty()) {
            int u = q.front().u, h = q.front().h;
            height[u] = h;
            q.pop();
            for (int v = 0; v < n; v++) {
                if (!vis[v] && cap[u][v] > flow[u][v]) {
                    q.push(Bfs(v, h + 1));
                    vis[v] = true;
                }
            }
        }
        return vis[n - 1];
    }
    int dfs(int u, int f) {
        int total_flow = 0;
        if (u == n - 1) return f;
        for(;ptr[u] < n; ptr[u]++) {
            int v = ptr[u];
            if (height[u] + 1 == height[v] && cap[u][v] > flow[u][v]) {
                int fl = dfs(v, min(f, cap[u][v] - flow[u][v]));
                flow[u][v] += fl;
                flow[v][u] -= fl;
                total_flow += fl;
                f -= fl;
                if (f == 0) break;
            }
        }
        return total_flow;
    }
public:
    Network(int n): n(n) {
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
    }
    void add_edge(int u, int v, int c) {
        cap[u][v] += c;
    }
    int max_flow() {
        int ret = 0;
        while (bfs()) {
            memset(ptr, 0, sizeof(ptr));
            ret += dfs(0, 2000000000);
        }
        return ret;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<ll> > dist(n, vector<ll>(n, INF));
    vector<int> in(n), out(n);
    for(int i = 0; i < n; i++) dist[i][i] = 0;
    int n_cow = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &in[i], &out[i]);
        n_cow += in[i];
    }
    for(int i = 0; i < m; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        dist[u - 1][v - 1] = min(dist[u - 1][v - 1], ll(d));
        dist[v - 1][u - 1] = min(dist[v - 1][u - 1], ll(d));
    }
    for(int l = 0; l < n; l++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][l] + dist[l][j]);
    set<ll> dist_set;
    dist_set.insert(0);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (dist[i][j] < INF) dist_set.insert(dist[i][j]);
    vector<ll> dists(dist_set.begin(), dist_set.end());
    int lo = 0, hi = dists.size();
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        Network net(n * 2 + 2);
        for(int i = 0; i < n; i++) {
            net.add_edge(0, i + 1, in[i]);
            net.add_edge(i + n + 1, n * 2 + 1, out[i]);
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(dist[i][j] <= dists[mid]) net.add_edge(i + 1, j + n + 1, 1000000000);
        if (net.max_flow() == n_cow) hi = mid;
        else lo = mid + 1;
    }
    printf("%lld\n", lo == dists.size() ? -1 : dists[lo]);
}