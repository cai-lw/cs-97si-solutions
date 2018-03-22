#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

class Network {
    int cap[201][201], flow[201][201];
    bool vis[201];
    int n;
    int dfs(int u, int f) {
        int ret = 0;
        if (u == n - 1) return f;
        vis[u] = true;
        for (int v = 0; v < n; v++)
            if (!vis[v] && cap[u][v] - flow[u][v] > 0) {
                ret = dfs(v, min(f, cap[u][v] - flow[u][v]));
                if (ret > 0) {
                    flow[u][v] += ret;
                    flow[v][u] -= ret;
                    break;
                }
            }
        return ret;
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
        int ret = 0, f;
        do {
            memset(vis, 0, sizeof(vis));
            f = dfs(0, 1000000000);
            ret += f;
        } while (f > 0);
        return ret;
    }
};

struct GEdge {
    int u, v, l;
    GEdge() {}
    GEdge(int u, int v, int l): u(u), v(v), l(l) {}
    bool operator<(const GEdge &other) const {
        return l < other.l;
    }
};

int main() {
    int n, p, t;
    scanf("%d %d %d", &n, &p, &t);
    vector<GEdge> graph(p);
    int min_l = 1000000, max_l = 0;
    for (int i = 0; i < p; i++) {
        int u, v, l;
        scanf("%d %d %d", &u, &v, &l);
        graph[i] = GEdge(u, v, l);
        max_l = max(max_l, l);
        min_l = min(min_l, l);
    }
    int lo = min_l, hi = max_l;
    while (lo < hi) {
        Network net(n + 1);
        net.add_edge(0, 1, t);
        int mid = (lo + hi) / 2;
        for (int i = 0; i < p; i++)
            if (graph[i].l <= mid) {
                net.add_edge(graph[i].u, graph[i].v, 1);
                net.add_edge(graph[i].v, graph[i].u, 1);
            }
        if (net.max_flow() == t) hi = mid;
        else lo = mid + 1;
    }
    printf("%d\n", lo);
}