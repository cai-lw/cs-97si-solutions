#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

struct Edge {
    int v;
    double c, f;
    Edge(int v, double c, double f): v(v), c(c), f(f) {}
};

struct Bfs {
    int u, h;
    Bfs(int u, int h): u(u), h(h) {}
};

int cmp(double x, double y) {
    const double eps = 1e-9;
    if (abs(x - y) < eps || abs(x - y) / max(abs(x), abs(y)) < eps) return 0;
    else return x > y ? 1 : -1;
}

class Network {
    vector<vector<int> > edge_ids;
    vector<Edge> edges;
    vector<int> height, ptr;
    bool bfs() {
        int n = edge_ids.size();
        queue<Bfs> q;
        vector<bool> vis(n);
        q.push(Bfs(0, 0));
        vis[0] = true;
        while(!q.empty()) {
            int u = q.front().u, h = q.front().h;
            height[u] = h;
            q.pop();
            for (int i = 0; i < edge_ids[u].size(); i++) {
                Edge &e = edges[edge_ids[u][i]];
                if (cmp(e.c, e.f) == 1 && !vis[e.v]) {
                    q.push(Bfs(e.v, h + 1));
                    vis[e.v] = true;
                }
            }
        }
        return vis[n - 1];
    }
    double dfs(int u, double f) {
        int n = edge_ids.size();
        double total_flow = 0;
        if (u == n - 1) return f;
        for(;ptr[u] < edge_ids[u].size(); ptr[u]++) {
            Edge &e = edges[edge_ids[u][ptr[u]]], &e_rev = edges[edge_ids[u][ptr[u]] ^ 1];
            if (height[u] + 1 == height[e.v] && cmp(e.c, e.f) == 1) {
                double flow = dfs(e.v, min(f, e.c - e.f));
                e.f += flow;
                e_rev.f -= flow;
                total_flow += flow;
                f -= flow;
                if (cmp(f, 0.0) == 0) break;
            }
        }
        return total_flow;
    }
public:
    Network(int n): edge_ids(n), height(n), ptr(n) {}
    void add_edge(int u, int v, double c) {
        edges.push_back(Edge(v, c, 0));
        edges.push_back(Edge(u, 0, 0));
        edge_ids[u].push_back(edges.size() - 2);
        edge_ids[v].push_back(edges.size() - 1);
    }
    double max_flow() {
        int n = edge_ids.size();
        double ret = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            ret += dfs(0, 1e9);
        }
        return ret;
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, l;
        scanf("%d %d %d", &n, &m, &l);
        Network net(n + m + 2);
        double cost;
        for(int i = 1; i <= n; i++) {
            scanf("%lf",&cost);
            net.add_edge(0, i, log(cost));
        }
        for(int i = n + 1; i <= n + m; i++) {
            scanf("%lf",&cost);
            net.add_edge(i, n + m + 1, log(cost));
        }
        for(int i = 0; i < l; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            net.add_edge(x, n + y, 1e9);
        }
        printf("%.4lf\n", exp(net.max_flow()));
    }
}